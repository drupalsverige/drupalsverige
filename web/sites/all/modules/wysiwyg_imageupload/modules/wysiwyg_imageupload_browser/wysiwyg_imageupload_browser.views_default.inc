<?php
// $Id$
// Copyright (c) 2010 KontextWork GbR
// Author: Eugen Mayer

function wysiwyg_imageupload_browser_views_default_views() {
  $view = new view;
  $view->name = 'wysiwyg_imageupload_browser';
  $view->description = 'Image Browser';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'wysiwyg_imageupload_entity';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'fid' => array(
      'label' => 'File',
      'required' => 1,
      'id' => 'fid',
      'table' => 'wysiwyg_imageupload_entity',
      'field' => 'fid',
      'relationship' => 'none',
    ),
    'nid' => array(
      'label' => 'Node',
      'required' => 1,
      'id' => 'nid',
      'table' => 'wysiwyg_imageupload_entity',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'iid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'wui_preset' => 'wysiwyg_imageupload_browser_preview',
      'wui_link_for_browser' => 1,
      'exclude' => 0,
      'preset' => 'wysiwyg_imageupload_browser_preview',
      'link_for_browser' => 1,
      'id' => 'iid',
      'table' => 'wysiwyg_imageupload_entity',
      'field' => 'iid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'nid' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'nid',
      'table' => 'node_access',
      'field' => 'nid',
      'relationship' => 'nid',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 6);
  $handler->override_option('use_pager', '1');
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '3',
    'alignment' => 'horizontal',
    'fill_single_line' => 1,
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'iid' => 'iid',
    ),
    'separator' => '',
    'hide_empty' => 1,
  ));

  $views = array();
  $views['wysiwyg_imageupload_browser'] = $view;
  return $views;
}
