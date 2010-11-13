<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_wysiwyg_imagecache_default_presets() {
  $items = array(
    'large' => array(
      'presetname' => 'large',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '680',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'medium' => array(
      'presetname' => 'medium',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '365',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'small' => array(
      'presetname' => 'small',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '155',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}
