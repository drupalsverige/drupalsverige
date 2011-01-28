<?php
// $Id: addtoany.views.inc,v 1.1.2.2 2010/06/27 06:13:21 micropat Exp $

/**
 * @file
 * Views integration for AddToAny.
 */

/**
 * Implementation of hook_views_data().
 */
function addtoany_views_data() {
  // Add the addtoany link to the node fields
  $data['node']['addtoany_link'] = array(
    'title' => t('AddToAny link'),
    'help' => t('Link provided by the AddToAny module'),
    'field' => array(
      'handler' => 'addtoany_handler_field_addtoany_link',
      'click sortable' => FALSE,
    )
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function addtoany_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'addtoany') . '/views',
    ),
    'handlers' => array(
      'addtoany_handler_field_addtoany_link' => array(
        'parent' => 'views_handler_field_node_link',
      ),
    ),
  );
}