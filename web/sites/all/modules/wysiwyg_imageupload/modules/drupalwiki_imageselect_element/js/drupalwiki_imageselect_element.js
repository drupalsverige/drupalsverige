// $Id$

// Author: Eugen Mayer (http://kontextwork.de)
// Copyright 2010
Drupal.behaviors.drupalwiki_imageselect_element = function() {
  $('select.drupalwiki-imageselect-element:not(.drupalwiki-imageselect-element-processed)').drupalwiki_imageselect_element();
}