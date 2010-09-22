<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function drupalse_provider_taxonomy_default_vocabularies() {
  return array(
    'lan' => array(
      'name' => 'Län',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '1',
      'required' => '0',
      'tags' => '1',
      'module' => 'features_lan',
      'weight' => '0',
      'type' => NULL,
      'nodes' => array(),
    ),
  );
}
