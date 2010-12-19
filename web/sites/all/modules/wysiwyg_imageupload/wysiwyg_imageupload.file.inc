<?php
// $Id$

// Copyright (c) 2010 KontextWork
// Author: Eugen Mayer

/**
 * Uploading a image and calling the file_insert hooks.
 * @return: Returns the uploaded file as an object
 */
function _wysiwyg_imageupload_upload_file() {
  global $user;
  $dest = _wysiwyg_imageupload_get_dest_dir();
  // create the path if not existent
  if (!file_check_directory($dest)) {
    mkdir($dest, 0777, TRUE);
  }

  if (!file_check_directory($dest, FILE_CREATE_DIRECTORY)) {
    drupal_set_message('Destination path is not writeable, cant upload', 'error');
    return NULL;
  }

  $validators = array(
    'file_validate_is_image' => array()
  );
  $max_filesize = variable_get('wysiwyg_imageupload_max_filesize', 0) * 1000;
  if($max_filesize > 0) {
    $validators['file_validate_size'] =  array( $max_filesize , 0);
  }
  $file = NULL;
  if (user_access('use wysiwyg image upload') && $file = file_save_upload('wysiwyg_imageupload_file', $validators, $dest, FILE_EXISTS_RENAME)) {
    foreach (module_implements('wysiwyg_imageupload_image_uploaded') as $module) {
      $function =  $module .'_wysiwyg_imageupload_image_uploaded';
      $function($file);
    }

    $file->list = 0;  // do not list the images
    $file->description = $file->filename;
    $file->weight = 0;
    $file->new = TRUE;

    if (!@chmod($file->filepath, 0664)) {
      watchdog('wysiwyg_imageupload', 'Could not set permissons on destination file: %file', array('%file' => $file->filepath));
    }
  }
  else {
    // Upload failed.
    return NULL;
  }

  drupal_alter('wysiwyg_imageupload_file_uploaded', $file);
  return (object) $file;
}

/**
 * Get the dest dir by parsing the settings and calling other modules
 *
 */
function _wysiwyg_imageupload_get_dest_dir() {
  global $user;
  $dest = file_directory_path();
  // Add the global relativ path.
  $dest = "$dest/" . variable_get('wysiwyg_imageupload_dest_root', 'wysiwyg_imageupload');
  // If its not a guest and we have set a userpath, add it relativly.
  if ($user->uid > 0) {
    $userpath  = variable_get('wysiwyg_imageupload_relative_user', '$uid');
    if ($userpath != '') {
      $userpath  = str_replace("\$uid", $user->uid, variable_get('wysiwyg_imageupload_relative_user',  '$uid'));
      $dest = "$dest/$userpath";
    }
  }
  // Finally let other modules alter the path
  drupal_alter('wysiwyg_imageupload_dest_path', $dest);
  return $dest;
}

/**
 * Loading all files uploaded to a node
 */
function _wysiwyg_imageupload_load($node) {
  $files = array();
  if ($node->vid) {
    $result = db_query('SELECT * FROM {wysiwyg_imageupload_entity_revision} as r LEFT JOIN {wysiwyg_imageupload_entity} AS e ON r.iid=e.iid LEFT JOIN {files} as f ON f.fid = e.fid  WHERE r.vid = %d ', $node->vid);
    while ($file = db_fetch_object($result)) {
      $files[$file->iid] = $file;
    }
  }

  return $files;
}

/**
 * Loading all files uploaded to a comment
 */
function _wysiwyg_imageupload_commment_load($cid) {
  $files = array();

  $result = db_query('SELECT * FROM {files} f INNER JOIN {wysiwyg_imageupload_entity} r ON f.fid = r.fid WHERE r.cid = %d', $cid);
  while ($file = db_fetch_object($result)) {
    $files[$file->iid] = $file;
  }

  return $files;
}

/**
 * Share from the upload.module
 * Adds, removes or updates files in the image property.
 * This is actually the place where a file object get attached to a node, the
 * relation is saved in the wysiwyg_imageupload table
 */
function _wysiwyg_imageupload_save(&$entity) {
  if (!is_object($entity)) {
    // comments might be submitted as array.
    $entity = (object)$entity;
  }
  // how does that look like for a comment?
  if (!empty($entity->cid) && $entity->cid > 0) {
    _wysiwyg_imagegupload_save_images($entity, $entity->comment);
  }
  else {
    _wysiwyg_imagegupload_save_images($entity, $entity->body);

    $node = (array) $entity;
    foreach ($node as $key => $field) {
      if (strpos($key, 'field_') === 0) {
        foreach ($field as $index => $field_item) {
          if (!empty($field_item['value'])) {
            $value = $field_item['value'];
            _wysiwyg_imagegupload_save_images($entity, $value);
          }
        }
      }
    }
  }
}

/**
 * Auxiliary function for _wysiwyg_imageupload_save().
 */
function _wysiwyg_imagegupload_save_images(&$entity, $value) {
  $images = array();
  preg_match_all(_wysiwyg_imageupload_filter_pattern(), $value, $matches);

  if(empty($matches)) {
    return;
  }
  
  for($i=0; $i<count($matches[0]); $i++) {
    $iid =$matches[1][$i];
    // remove the widget from the array as all the restovers will be deleted then
    $images[$iid] = _wysiwyg_imageupload_load_inline_entity($iid);
  }

  foreach ($images as $iid => $file) {
    // Convert file to object for compatibility.
    $file = (object)$file;
    file_set_status($file, FILE_STATUS_PERMANENT);
    $data = array(
      'iid' => $file->iid,
      'temporary' => 0,
    );

    // It's a comment.
    if (!empty($entity->cid) && $entity->cid > 0) {
      $data['nid'] = $entity->nid;
      $data['cid'] = $entity->cid;
    }
    else {
      // Its a node.
      $data['nid'] = $entity->nid;
      $data['cid'] = 0;
      // Create a new revision, or associate a new file needed.
      _wysiwyg_imageupload_create_revision($iid, $entity->vid);
    }
    drupal_write_record('wysiwyg_imageupload_entity', $data, array('iid'));
      // Call the alter hooks to react on the current attached image entity.
    $data = (object) $data;
    drupal_alter('wysiwyg_imageupload_image_entity_attached', $data);
  }
}

/**
 * Cleanup all wui entries which have no corresponding file objects anymore
 */
function _wysiwyg_imageupload_cleanup_temps() {
  db_query('DELETE wui,wuir FROM {wysiwyg_imageupload_entity} AS wui LEFT JOIN {wysiwyg_imageupload_entity_revision} AS wuir ON wui.iid=wuir.iid WHERE NOT EXISTS (SELECT fid from {files} as f WHERE wui.fid=f.fid)');
}

/**
 * Deletes all inline entities for a specific node
 * If the correspinding files are not using in any other node, they will be deleted
 */
function _wysiwyg_imageupload_handle_node_delete($nid) {
  $entities = array();
  // Get all current entities to later be able to look if their files are still in use.
  $result = db_query('SELECT * FROM {wysiwyg_imageupload_entity} WHERE nid=%d', $nid);
  while ($entity = db_fetch_object($result)) {
    $entities[] = $entity;
  }
  // Delete all inline entities for all version.
  db_query('DELETE e,r FROM {wysiwyg_imageupload_entity} AS e LEFT JOIN {wysiwyg_imageupload_entity_revision} AS r ON e.iid=r.iid WHERE nid=%d', $nid);

  // Cleanup files which are no longer used.
  foreach ($entities as $entity) {
    // Calling other modules to veto the file deletion
    $result = module_invoke_all('wysiwyg_imageupload_veto_file_deletion', $entity->fid);
    $do_not_delete = FALSE;
    if (is_array($result)) {
      foreach ($result as $val) {
        $do_not_delete |= $val;
      }
    }

    if ($do_not_delete) {
      continue;
    }
    $filepath = db_result(db_query('SELECT filepath FROM {files} WHERE fid = %d', $entity->fid));
    if (!empty($filepath)) {
      file_delete($filepath);
      db_query('DELETE FROM {files} WHERE fid = %d', $entity->fid);
    }
  }
}

/*
 * Implementation of hook_wysiwyg_imageupload_veto_file_deletion().
 * Check if the image is used in a other node (inserted using the browser) and deny deletion
 */
function wysiwyg_imageupload_wysiwyg_imageupload_veto_file_deletion($fid) {
  $count = db_result(db_query('SELECT COUNT(fid) FROM {wysiwyg_imageupload_entity} WHERE fid=%d', $fid));
  // If this file is used somewhere else ( this image) dont delete it
  if ($count > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Updates or revision table for inline images and adds a new revision
 */
function _wysiwyg_imageupload_create_revision($iid, $vid) {
  $idd = db_result(db_query_range('SELECT iid FROM {wysiwyg_imageupload_entity_revision} WHERE iid=%d AND vid=%d', $iid, $vid, 0, 1));
  if ($idd) {
    // version already exists, dont create a new one
    return FALSE;
  }
  $data = array(
    'iid' => $iid,
    'vid' => $vid
  );

  drupal_write_record('wysiwyg_imageupload_entity_revision', $data);
  return TRUE;
}

/**
 * Loads the inline-image object with all its details
 */
function _wysiwyg_imageupload_load_inline_entity($iid) {
  $result = db_query_range('SELECT inl.*,f.*,er.vid FROM {wysiwyg_imageupload_entity} AS inl LEFT JOIN {wysiwyg_imageupload_entity_revision} as er ON inl.iid=er.iid LEFT JOIN {files} AS f ON inl.fid=f.fid WHERE inl.iid=%d', $iid, 0, 1);
  if ($result !== FALSE) {
    $img_obj = db_fetch_object($result);
    drupal_alter('wysiwyg_imageupload_entity_load', $img_obj, $iid);
    return $img_obj;
  }
  // else
  return FALSE;
}

/**
 * Create a basic / dummy inline-image entity which will be filled later
 */
function _wysiwyg_imageupload_create_inline_entity($file, $temporary = TRUE, $options = array()) {
  $record = array(
    'fid' => $file->fid,
    'temporary' => $temporary,
  );
  $record = array_merge($record, $options);

  drupal_write_record('wysiwyg_imageupload_entity', $record);
  return $record['iid'];
}

function wysiwyg_imageupload_cron() {
  _wysiwyg_imageupload_cleanup_temps();
}
