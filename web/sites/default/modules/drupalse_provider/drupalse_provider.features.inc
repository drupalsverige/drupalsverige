<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function drupalse_provider_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_provider_imagecache_default_presets() {
  $items = array(
    'provider-logo' => array(
      'presetname' => 'provider-logo',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '200',
            'height' => '',
            'upscale' => 0,
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '',
            'height' => '100',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function drupalse_provider_node_info() {
  $items = array(
    'provider' => array(
      'name' => t('Leverantör'),
      'module' => 'features',
      'description' => t('En leverantör av Drupaltjänster i Sverige.'),
      'has_title' => '1',
      'title_label' => t('Företagsnamn'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function drupalse_provider_views_api() {
  return array(
    'api' => '2',
  );
}
