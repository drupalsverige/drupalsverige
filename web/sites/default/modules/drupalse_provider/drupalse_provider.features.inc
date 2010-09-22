<?php

/**
 * Implementation of hook_node_info().
 */
function drupalse_provider_node_info() {
  $items = array(
    'provider' => array(
      'name' => t('Leverantör'),
      'module' => 'features',
      'description' => '',
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
