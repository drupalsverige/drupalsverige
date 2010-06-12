<?php
// $Id: better_exposed_filters_exposed_form_plugin.inc,v 1.11 2010/05/25 17:36:47 mikeker Exp $

/**
 * @file
 * Provides an Better Exposed Filters exposed form plugin for View 3.x.
 */
class better_exposed_filters_exposed_form_plugin extends views_plugin_exposed_form_basic {

  function summary_title() {
    return t('Better Exposed Filters');
  }

  function option_definition() {
    $options = parent::option_definition();

    // Add Better Exposed Filters options to those saved by Views
    $options['bef'] = array('default' => array());

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    /*
     * Changes to the options form need to be mirrored in hook_form_alter in 
     * better_exposed_filters.module to maintain Views 2.x support 
     */
    
    $bef_options = array();

    // Go through each filter and add the same options we used to add in hook_form_alter()
    foreach ($this->display->handler->get_handlers('filter') as $label => $filter) {
      if (!$filter->options['exposed']) {
        continue;
      }

      // Is this a type of field we can't tweak?  (eg: text fields)
      if (('=' == $filter->operator) && !is_bool($filter->value)) {
        // others?
        continue;
      }

      // Main BEF option: default/checkboxes/hidden
      $bef_options[$label]['bef_format'] = array(
        '#type' => 'select',
        '#title' => t('Display "@label" exposed filter as', array('@label' => $filter->options['expose']['label'])),
        '#default_value' => $this->options['bef'][$label]['bef_format'],
        '#options' => array(
          'default' => t('Default select list'),
          'bef' => t('Checkboxes/Radio Buttons'),
          'bef_hidden' => t('Hidden'),
        ),
        '#description' => t(
          'Select a format for the exposed filter.  The "Hidden" option is 
            generally used for multi-step filters.  Note: if "Force single" 
            is checked, radio buttons will be used.  If "Force single" is 
            unchecked, checkboxes will be used.' 
        ),
      );

      // Fieldset to keep the UI from getting out of hand
      $bef_options[$label]['more_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('More options for "@label"', array('@label' => $filter->options['expose']['label'])),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Select all checkbox
      $bef_options[$label]['more_options']['bef_select_all_none'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add select all/none links'),
        '#default_value' => $this->options['bef'][$label]['more_options']['bef_select_all_none'],
        '#disabled' => $filter->options['expose']['single'],
        '#description' => t(
          'Add a "Select All/None" link when rendering the exposed filter using 
            checkboxes. If this option is disabled, edit the filter and uncheck
            "Force single". NOTE: The link is built at page load, so it will not appear
            in the "Live Preview" which is loaded dynamically.'
        ),
      );

      // Build a description option form element
      $bef_options[$label]['more_options']['bef_filter_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $this->options['bef'][$label]['more_options']['bef_filter_description'],
        '#description' => t('Adds descriptive text to the exposed filter.  This is usually 
                              rendered in smaller print under the label or the options.'),
      );
    }             // foreach ($filters as $filter) {

    // Add BEF form elements to the exposed form options form
    $form['bef'] = $bef_options;
  }

  /*
   * Tweak the exposed filter form to show Better Exposed Filter options.
   */
  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);
    
    /*
     * Changes to the display of BEF filters need to be mirrored in hook_form_alter in 
     * better_exposed_filters.module to maintain Views 2.x support 
     */
    
    // Shorthand for all filters in this view
    $filters = $form_state['view']->display_handler->handlers['filter'];
    
    // Go through each saved option looking for Better Exposed Filter settings
    foreach ($this->options['bef'] as $label => $options) {

      // Sanity check: Ensure this filter is an exposed filter
      if (!$filters[$label]->options['exposed']) {
        continue;
      }
      
      // Form element is designated by the element ID which is user-configurable
      $field_id = $form['#info']["filter-$label"]['value'];

      // Add a description to the exposed filter
      if (!empty($options['more_options']['bef_filter_description'])) {
        $form[$field_id]['#description'] = $options['more_options']['bef_filter_description'];
      } 
        
      switch ($options['bef_format']) {
        case 'bef':
          if (empty($form[$field_id]['#multiple'])) {
            // For "force-single" select boxes or other single-select options, just switch to 
            // radio buttons.
            $form[$field_id]['#type'] = 'radios';
            $form[$field_id]['#process'] = array('expand_radios', 'views_process_dependency');
            $form[$field_id]['#prefix'] = '<div class="bef-select-as-radios">';
            $form[$field_id]['#suffix'] = '</div>';

            if (isset($form[$field_id]['#options']['All'])) {
              // @TODO: The terms 'All' and 'Any' are customizable in Views
              if (!$filters[$label]->options['expose']['optional']) {
                // Some third-party filter handlers still add the "Any" option even if this is not
                // an optional filter.  Zap it here if they do. 
                unset($form[$field_id]['#options']['All']);
              }
              else {
                // Otherwise, make sure the "Any" text is clean
                $form[$field_id]['#options']['All'] = check_plain($form[$field_id]['#options']['All']);
              }
            }
          }
          else {
            // For multi-select boxes, rewrite the HTML at the theme level, since the Forms API handles
            // selects and checkboxes differently.
            $form[$field_id]['#theme'] = 'select_as_checkboxes';
            if ($options['more_options']['bef_select_all_none']) {
              // Add BEF's JavaScript to the mix to handle select all/none functionality
              drupal_add_js(drupal_get_path('module', 'better_exposed_filters') .'/better_exposed_filters.js');

              // Add select all/none functionality to this filter.
              if (!isset($form[$field_id]['#attributes'])) {
                $form[$field_id]['#attributes'] = array();
              }
              
              // If the 'class' index doesn't exist, PHP will throw a notice if the error_reporting
              // level includes E_NOTICE.  Suppress the notice with the '@' operator. 
              @$form[$field_id]['#attributes']['class'] .= 'bef-select-all-none';
            }
          }
          break;
              
        case 'bef_hidden':
          $form['#info']["filter-$field_id"]['label'] = '';     // Hide the label
          if (empty($form[$field_id]['#multiple'])) {
            $form[$field_id]['#type'] = 'hidden';
          }
          else {
            $form[$field_id]['#theme'] = 'select_as_hidden';
          }
          break;
          
      }     // switch ($options['bef_format'])
    }       // foreach ($this->options['bef']...)
  }         // function exposed_form_alter(...)
}