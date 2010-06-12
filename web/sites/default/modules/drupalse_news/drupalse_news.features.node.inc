<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _drupalse_news_node_info() {
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
