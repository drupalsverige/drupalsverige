<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_showcase_imagecache_default_presets() {
  $items = array(
    'showcase_thumb' => array(
      'presetname' => 'showcase_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '350',
            'height' => '',
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
function drupalse_showcase_node_info() {
  $items = array(
    'showcase' => array(
      'name' => t('Showcase'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Sajtnamn'),
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
function drupalse_showcase_views_api() {
  return array(
    'api' => '2',
  );
}
