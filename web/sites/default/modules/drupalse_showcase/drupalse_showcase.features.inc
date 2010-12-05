<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function drupalse_showcase_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_showcase_imagecache_default_presets() {
  $items = array(
    'showcase_small_thumb' => array(
      'presetname' => 'showcase_small_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '185',
            'height' => '115',
          ),
        ),
      ),
    ),
    'showcase_thumb' => array(
      'presetname' => 'showcase_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '350',
            'height' => '230',
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
      'description' => t('En Drupalwebbplats som är värld att lyfta fram på drupalsverige.se. Showcases kan markeras för visning på förstasidan, sorteras som svenska eller utländska/internationella webbplatser, och även länka till leverantörer.'),
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
