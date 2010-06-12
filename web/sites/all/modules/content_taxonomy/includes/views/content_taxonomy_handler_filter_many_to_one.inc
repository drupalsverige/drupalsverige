<?php

/**
 * Subclass of views_handler_filter_many_to_one_content
 *
 * provides values for the filters
 * unsets the empty value for non required fields, which is added content_taxonomy_allowed_values
 */
class content_taxonomy_handler_filter_many_to_one extends content_handler_filter_many_to_one {
  var $content_field;

  function construct() {
    parent::construct();
  }

  function get_value_options() {
    $options = content_taxonomy_allowed_values($this->content_field);
    unset($options['']);
    $this->value_options = $options;
  }
}
