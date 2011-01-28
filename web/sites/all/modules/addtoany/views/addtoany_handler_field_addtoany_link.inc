<?php
// $Id: addtoany_handler_field_addtoany_link.inc,v 1.1.2.2 2010/06/27 06:13:21 micropat Exp $

/**
 * @file
 * Views field handler for the AddToAny link field
 */

/**
 * Field handler to present AddToAny links.
 */
class addtoany_handler_field_addtoany_link extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['title'] = 'title';
  }

  function render($values) {
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->title = $values->{$this->aliases['title']};

    return _addtoany_create_button($node, $teaser);
  }
}
