<?php
// $Id: semanticviews.theme.inc,v 1.1.2.1 2010/04/10 04:07:25 bangpound Exp $
/**
 * @file semanticviews.theme.inc
 * TODO: Enter file description here.
 */

/**
 * Preprocess theme function to print a single record from a row, with fields
 */
function template_preprocess_semanticviews_view_fields(&$vars) {
  $view = $vars['view'];

  // Loop through the fields for this view.
  $vars['fields'] = array(); // ensure it's at least an empty array.
  foreach ($view->field as $id => $field) {
    // render this even if set to exclude so it can be used elsewhere.
    $field_output = $view->style_plugin->get_field($view->row_index, $id);
    $empty = $field_output !== 0 && empty($field_output);
    if (empty($field->options['exclude']) && !(($vars['options']['skip_blank'] || $field->options['hide_empty']) && $empty)) {
      $object = new stdClass();

      $object->content = $field_output;
      if (isset($view->field[$id]->field_alias) && isset($vars['row']->{$view->field[$id]->field_alias})) {
        $object->raw = $vars['row']->{$view->field[$id]->field_alias};
      }
      else {
        $object->raw = NULL; // make sure it exists to reduce NOTICE
      }

      $object->handler = &$view->field[$id];

      $semantic_html = $vars['options']['semantic_html'][$id];

      // Field content
      $object->element_type = check_plain($semantic_html['element_type']);
      $object->attributes = array();
      if ($semantic_html['class']) {
        $object->attributes['class'] = $semantic_html['class'];
      }

      // Field label
      $object->label = check_plain($view->field[$id]->label());
      if (!empty($object->label)) {
        $object->label_element_type = check_plain($semantic_html['label_element_type']);
        $object->label_attributes = array();
        if ($semantic_html['label_class']) {
          $object->label_attributes['class'] = $semantic_html['label_class'];
        }
      }

      $vars['fields'][$id] = $object;
    }
  }

}

/**
 * Display the simple view of rows one after another
 */
function template_preprocess_semanticviews_view_unformatted(&$vars) {
  $view = $vars['view'];

  $vars['group_element'] = check_plain($vars['options']['group']['element_type']);
  $vars['group_attributes'] = array();
  if ($vars['options']['group']['class']) {
    $vars['group_attributes']['class'] = $vars['options']['group']['class'];
  }

  $vars['list_element'] = check_plain($vars['options']['list']['element_type']);
  $vars['list_attributes'] = array();
  if ($vars['options']['list']['class']) {
    $vars['list_attributes']['class'] = $vars['options']['list']['class'];
  }

  // TODO: set a default or handle empty value.
  $vars['row_element'] = check_plain($vars['options']['row']['element_type']);
  $last_every_nth = $vars['options']['row']['last_every_nth'];

  $vars['row_attributes'] = array();

  // Set up striping class array.
  $stripes = array();
  if (trim($vars['options']['row']['striping_classes'])) {
    $stripes = explode(' ', trim($vars['options']['row']['striping_classes']));
  }
  $striping = count($stripes);

  // Get alias tokens.
  $tokens = semanticviews_get_alias_tokens($view);

  foreach ($vars['rows'] as $id => $row) {
    // Get token replacements.
    $replacements = semanticviews_get_token_replacements($view->result[$id], $tokens);
    // Add replacement for the row number.
    $replacements['#'] = $id;

    $vars['row_attributes'][$id] = array();
    $classes = array();
    if ($vars['options']['row']['class']) {
      $classes[] = strtr($vars['options']['row']['class'], $replacements);
    }
    if ($vars['options']['row']['first_class']) {
      // The FIRST class attribute can be used in two ways. When the "last every
      // nth" option is specified, the FIRST attribute is added to the class in
      // those intervals. This could be useful for grid designs where the first
      // unit in a row needs a zero width margin.
      if (($last_every_nth && $id % $last_every_nth == 0) ||
         // Otherwise when last every nth is not set, the FIRST class is added
         // to the first row in the pager set.
         (!$last_every_nth && $id == 0)) {
        $classes[] = strtr($vars['options']['row']['first_class'], $replacements);
      }
    }
    if ($vars['options']['row']['last_class']) {
      // The LAST class attribute can be used in two ways. When the "last every
      // nth" option is specified, the LAST attribute is added to the class in
      // those intervals. This could be useful for grid designs where the last
      // unit in a row needs a zero width margin.
      if (($last_every_nth && ($id + 1) % $last_every_nth == 0) ||
         // Otherwise when last every nth is not set, the LAST class is added
         // to the last row in the pager set.
         (!$last_every_nth && ($id + 1) == count($vars['rows']))) {
        $classes[] = strtr($vars['options']['row']['last_class'], $replacements);
      }
    }

    if ($striping) {
      $classes[] = strtr($stripes[$id % $striping], $replacements);
    }

    if (!empty($classes)) {
      $vars['row_attributes'][$id]['class'] = implode(' ', $classes);
    }
  }
}
