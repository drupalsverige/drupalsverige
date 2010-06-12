<?php

/**
 * Implementation of hook_views_handlers().
 */
function content_taxonomy_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'content_taxonomy') . '/includes/views',
    ),
    'handlers' => array(
      'content_taxonomy_handler_filter_many_to_one' => array(
        'parent' => 'content_handler_filter_many_to_one',
      ),
    ),
  );
}
