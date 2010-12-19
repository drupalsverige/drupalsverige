<?php
// $Id$
class wysiwyg_imageupload_handler_field_image extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->additional_fields['iid'] = 'iid';
    $this->field_alias = 'iid';
  }
  function query() {
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = array();
    $options = parent::option_definition();
    $options['wui_preset'] = array('default' => TRUE);
    $options['wui_link_for_browser'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $presets = imagecache_presets();
    $styles = array();
    foreach ($presets as $preset) {
      // We can use the presetid here (http://drupal.org/node/694188).
      $styles[$preset['presetname']] = t("!preset", array('!preset' => $preset['presetname']));
    }
    $form['wui_preset'] = array(
      '#type' => 'select',
      '#title' => t('Use this imagecache preset'),
      '#default_value' =>  $this->options['wui_preset'],
      '#options' => $styles,
    );

    $form['wui_link_for_browser'] = array(
      '#type' => 'checkbox',
      '#title' => t('Create links on the images (for use in the image browser workflow)'),
      '#default_value' =>  $this->options['wui_link_for_browser']
    );
    return $form;
  }

  function render($values) {
    $img_obj =  _wysiwyg_imageupload_load_inline_entity($values->{$this->field_alias});
    $output = theme('imagecache', $this->options['wui_preset'], $img_obj->filepath, NULL, $img_obj->title);
    $parent_build_id = $this->view->args[0];
    if ($this->options['wui_link_for_browser'] == 1) {
      $output = l($output, 'wysiwyg_imageupload/reuse/' . $img_obj->iid . "/$parent_build_id", array(
        'title' => t('Insert this image'),
        'html' => 'true',
        'absolute' => TRUE
      ));
    }
    return $output;
  }
}
