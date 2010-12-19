<?php
// $Id$
class wysiwyg_imageupload_handler_field_images extends views_handler_field_prerender_list {
  function init(&$view, &$options) {
    $this->options['type'] = 'list';
    parent::init($view, $options);
    if ($view->base_table == 'node_revisions') {
      $this->additional_fields['vid'] = array('table' => 'node_revisions', 'field' => 'vid');
    }
    else {
      $this->additional_fields['vid'] = array('table' => 'node', 'field' => 'vid');
      $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
    }
  }
  function query() {
    $this->add_additional_fields();
  }

  function pre_render($values) {
    $vids = array();
    $this->items = array();

    $this->field_alias = $this->aliases['vid'];
    foreach ($values as $result) {
      if ($result->{$this->aliases['vid']}) {
        $vids[] = $result->{$this->aliases['vid']};
      }
    }
    $iids = wysiwyg_imageupload_get_images_by_vids($vids);
    foreach ($iids as $item) {
      $this->items[$item['vid']][$item['iid']] = $item;
    }
    $this->items[$this->field_alias] = $iids;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['wui_preset'] = array('default' => TRUE);
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

    return $form;
  }

  function render_item($key, $value) {
    $img_obj = (object) $value;
    return theme('imagecache', $this->options['preset'], $img_obj->filepath, NULL, $img_obj->title);
  }
}
