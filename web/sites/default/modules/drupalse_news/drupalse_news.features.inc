<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function drupalse_news_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_news_imagecache_default_presets() {
  $items = array(
    'news_thumbnail' => array(
      'presetname' => 'news_thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '200px',
            'height' => '200px',
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
function drupalse_news_node_info() {
  $items = array(
    'news' => array(
      'name' => t('Nyhet'),
      'module' => 'features',
      'description' => t('En nyhet postas på nyhetssidan.'),
      'has_title' => '1',
      'title_label' => t('Titel'),
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
function drupalse_news_views_api() {
  return array(
    'api' => '2',
  );
}
