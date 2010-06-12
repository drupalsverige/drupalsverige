<?php

/**
 * Implementation of hook_content_default_fields().
 */
function drupalse_provider_content_default_fields() {
  module_load_include('inc', 'drupalse_provider', 'drupalse_provider.defaults');
  $args = func_get_args();
  return call_user_func_array('_drupalse_provider_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function drupalse_provider_node_info() {
  module_load_include('inc', 'drupalse_provider', 'drupalse_provider.features.node');
  $args = func_get_args();
  return call_user_func_array('_drupalse_provider_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function drupalse_provider_views_default_views() {
  module_load_include('inc', 'drupalse_provider', 'drupalse_provider.features.views');
  $args = func_get_args();
  return call_user_func_array('_drupalse_provider_views_default_views', $args);
}
