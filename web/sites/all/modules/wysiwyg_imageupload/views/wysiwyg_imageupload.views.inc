<?php
// $Id$
/**
 * @file
 * Provide views integration for wysiwyg.
 */

/**
 * Implements hook_views_data().
 */


function wysiwyg_imageupload_views_data() {
  $data = array();
  _wysiwyg_imageupload_views_data_node_related($data);
  _wysiwyg_imageupload_views_data_all_entities($data);
  return $data;
}

function _wysiwyg_imageupload_views_data_node_related(&$data) {
  $data['wysiwyg_imageupload_entity_revision']['table']['group']  = t('Wysiwyg image upload');

  // This displays a image, will all goodies, therefore it needs a extra handler.
  $data['wysiwyg_imageupload_entity_revision']['iid'] = array(
    'title' => t('Images'),
    'help' => t('All images of all nodes.'),
    'field' => array(
      'handler' => 'wysiwyg_imageupload_handler_field_images',
      'click sortable' => FALSE,
    ),
    // @TODO Perhaps someone needs a filter/sort here, but i cannot imagine this.
  );

  $data['wysiwyg_imageupload_entity_revision']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revision' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  $data['wysiwyg_imageupload_entity_revision']['vid'] = array(
    'title' => t('Nodes'),
    'help' => t('The nodes'),
    'relationship' => array(
      'label' => t('Node'),
      'base' => 'node',
      'base field' => 'vid',
      'handler' => 'views_handler_relationship',
    ),
  );
}

function _wysiwyg_imageupload_views_data_all_entities(&$data) {
  $data['wysiwyg_imageupload_entity']['table']['group']  = t('Wysiwyg image upload');

  $data['wysiwyg_imageupload_entity']['table']['base'] = array(
    'field' => 'iid',
    'title' => t('WYSIWYG image upload'),
    'help' => t("An image uploaded via wysiwyg imageupload."),
  );

  $data['wysiwyg_imageupload_entity']['table']['join'] = array(
    'wysiwyg_imageupload_entity_revision' => array(
      'left_field' => 'iid',
      'field' => 'iid',
    ),
    'files' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  // This displays a image, will all goodies, therefore it needs a extra handler.
  $data['wysiwyg_imageupload_entity']['iid'] = array(
    'title' => t('Rendered image'),
    'help' => t('Rendered image'),
    'field' => array(
      'handler' => 'wysiwyg_imageupload_handler_field_image',
      'click sortable' => FALSE,
    ),
    // @TODO Perhaps someone needs a filter/sort here, but i cannot imagine this.
  );

  $data['wysiwyg_imageupload_entity']['title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the image.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['wysiwyg_imageupload_entity']['imagecache'] = array(
    'title' => t('imagecache'),
    'help' => t('The imagecache preset of the image.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['wysiwyg_imageupload_entity']['alignment'] = array(
    'title' => t('alignment'),
    'help' => t('The alignment of the image.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['wysiwyg_imageupload_entity']['style'] = array(
    'title' => t('Style'),
    'help' => t('The Style of the image.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['wysiwyg_imageupload_entity']['temporary'] = array(
    'title' => t('temporary'),
    'help' => t('Is the image temporary.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a title as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_boolean',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Here comes the cool stuff, relationships!!
  $data['wysiwyg_imageupload_entity']['fid'] = array(
    'title' => t('Files'),
    'help' => t('The uploaded file'),
    'relationship' => array(
      'label' => t('File'),
      'base' => 'files',
      'base field' => 'fid',
      'handler' => 'views_handler_relationship',
    ),
  );
  $data['wysiwyg_imageupload_entity']['nid'] = array(
    'title' => t('Nodes'),
    'help' => t('The nodes'),
    'relationship' => array(
      'label' => t('Node'),
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
    ),
  );
  return $data;
}
/**
 * Implements hook_vies_data_alter().
 */
function wysiwyg_imageupload_views_data_alter(&$data) {
  $data['files']['join']['table']['wysiwyg_imageupload_entity'] = array(
    'left_field' => 'fid',
    'field' => 'fid',
  );
}

/**
 * Implements hook_views_handlers().
 */
function wysiwyg_imageupload_views_handlers() {
  return array(
    'handlers' => array(
      'wysiwyg_imageupload_handler_field_images' => array(
        'parent' => 'views_handler_field_prerender_list',
        'path' => drupal_get_path('module', 'wysiwyg_imageupload') . '/views'
      ),
      'wysiwyg_imageupload_handler_field_image' => array(
        'parent' => 'views_handler_field',
        'path' => drupal_get_path('module', 'wysiwyg_imageupload') . '/views'
      ),
      // Filters
    ),
  );
}

