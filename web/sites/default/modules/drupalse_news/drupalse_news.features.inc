<?php

/**
 * Implementation of hook_content_default_fields().
 */
function drupalse_news_content_default_fields() {
  module_load_include('inc', 'drupalse_news', 'drupalse_news.defaults');
  $args = func_get_args();
  return call_user_func_array('_drupalse_news_content_default_fields', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_news_imagecache_default_presets() {
  module_load_include('inc', 'drupalse_news', 'drupalse_news.defaults');
  $args = func_get_args();
  return call_user_func_array('_drupalse_news_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function drupalse_news_node_info() {
  module_load_include('inc', 'drupalse_news', 'drupalse_news.features.node');
  $args = func_get_args();
  return call_user_func_array('_drupalse_news_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function drupalse_news_views_default_views() {
  module_load_include('inc', 'drupalse_news', 'drupalse_news.features.views');
  $args = func_get_args();
  return call_user_func_array('_drupalse_news_views_default_views', $args);
}
