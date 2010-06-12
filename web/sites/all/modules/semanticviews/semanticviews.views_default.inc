<?php
// $Id: semanticviews.views_default.inc,v 1.1.2.4 2010/04/10 03:27:17 bangpound Exp $

/**
 * Implementation of hook_views_default_views().
 */
function semanticviews_views_default_views() {
  /*
   * View 'semantic_demo'
   */
  $view = new view;
  $view->name = 'semantic_demo';
  $view->description = '';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE;
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
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
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'type' => array(
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
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'teaser' => array(
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
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'teaser',
      'table' => 'node_revisions',
      'field' => 'teaser',
      'relationship' => 'none',
    ),
    'delete_node' => array(
      'label' => 'Delete link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'text' => '',
      'exclude' => 0,
      'id' => 'delete_node',
      'table' => 'node',
      'field' => 'delete_node',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Edit link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Semantic Views demo');
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler = $view->new_display('page', 'Unformatted (default)', 'page_1');
  $handler->override_option('path', 'semantic-views-demo/unformatted');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Unformatted',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Semantic Views demo',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Grid (default)', 'page_2');
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '4',
    'alignment' => 'horizontal',
  ));
  $handler->override_option('path', 'semantic-views-demo/grid');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Grid',
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'List (default)', 'page_3');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler->override_option('path', 'semantic-views-demo/list');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'List',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Unformatted (semantic)', 'page_4');
  $handler->override_option('style_plugin', 'semanticviews_default');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'group' => array(
      'element_type' => 'h3',
      'class' => 'title',
    ),
    'list' => array(
      'element_type' => '',
      'class' => '',
    ),
    'row' => array(
      'element_type' => 'div',
      'class' => '',
      'last_every_nth' => '0',
      'first_class' => 'first',
      'last_class' => 'last',
      'striping_classes' => 'odd even',
    ),
  ));
  $handler->override_option('row_plugin', 'semanticviews_fields');
  $handler->override_option('row_options', array(
    'semantic_html' => array(
      'title' => array(
        'element_type' => 'h2',
        'class' => 'title',
      ),
      'type' => array(
        'element_type' => 'div',
        'class' => 'node-type',
      ),
      'teaser' => array(
        'element_type' => '',
        'class' => '',
      ),
      'delete_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
      'edit_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
    ),
    'skip_blank' => 1,
  ));
  $handler->override_option('path', 'semantic-views-demo/unformatted-semantic');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Unformatted (semantic)',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Grid (semantic)', 'page_5');
  $handler->override_option('header', '<style>
  .grid-unit {
    width: 20%;
    margin-right: 5%;
    float: left;
  }
  .first {
    clear: left;
  }
  .last {
    margin-right: 0;
  }
  </style>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 0);
  $handler->override_option('style_plugin', 'semanticviews_default');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'group' => array(
      'element_type' => 'h3',
      'class' => 'title',
    ),
    'list' => array(
      'element_type' => '',
      'class' => '',
    ),
    'row' => array(
      'element_type' => 'div',
      'class' => 'grid-unit',
      'last_every_nth' => '4',
      'first_class' => 'first',
      'last_class' => 'last',
      'striping_classes' => 'odd even',
    ),
  ));
  $handler->override_option('row_plugin', 'semanticviews_fields');
  $handler->override_option('row_options', array(
    'semantic_html' => array(
      'title' => array(
        'element_type' => 'h2',
        'class' => 'title',
      ),
      'type' => array(
        'element_type' => 'div',
        'class' => 'node-type',
      ),
      'teaser' => array(
        'element_type' => '',
        'class' => '',
      ),
      'delete_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
      'edit_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
    ),
    'skip_blank' => 1,
  ));
  $handler->override_option('path', 'semantic-views-demo/grid-semantic');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Grid (semantic)',
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'List (semantic)', 'page_6');
  $handler->override_option('style_plugin', 'semanticviews_default');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'group' => array(
      'element_type' => 'h3',
      'class' => 'title',
    ),
    'list' => array(
      'element_type' => 'ul',
      'class' => '',
    ),
    'row' => array(
      'element_type' => 'li',
      'class' => '',
      'last_every_nth' => '0',
      'first_class' => 'first',
      'last_class' => 'last',
      'striping_classes' => 'odd even',
    ),
  ));
  $handler->override_option('row_plugin', 'semanticviews_fields');
  $handler->override_option('row_options', array(
    'semantic_html' => array(
      'title' => array(
        'element_type' => 'h2',
        'class' => 'title',
      ),
      'type' => array(
        'element_type' => 'div',
        'class' => 'node-type',
      ),
      'teaser' => array(
        'element_type' => '',
        'class' => '',
      ),
      'delete_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
      'edit_node' => array(
        'element_type' => 'div',
        'class' => '',
        'label_element_type' => '',
        'label_class' => '',
      ),
    ),
    'skip_blank' => 1,
  ));
  $handler->override_option('path', 'semantic-views-demo/list-semantic');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'List (semantic)',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  return $views;
}


