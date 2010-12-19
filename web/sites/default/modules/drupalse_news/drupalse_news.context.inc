<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function drupalse_news_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'news';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~galleri' => '~galleri',
        '~news' => '~news',
        '~nyheter' => '~nyheter',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-news_listing-block_1' => array(
          'module' => 'views',
          'delta' => 'news_listing-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  $export['news'] = $context;
  return $export;
}
