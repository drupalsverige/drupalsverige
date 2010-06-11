<?php
//$id$
/**
 * @file
 * This is a sample drush alias file, which
 * you can use to contact the remote development
 * server through drush.
 * 
 * In order to be able to use this alias, you
 * need to have your key added to authorized keys
 * on the server.
 * 
 * Put this file in your .drush folder in or any
 * other appropriate folder that drush checks.
 * 
 * @todo
 * We currently have problems with the database syncing
 * on the server. Don't be alarmed if it doesn't work =)
 */

/**
 * This is the alias for the remote server
 */
$aliases['drupalse'] = array(
  'root' => '/var/www/drupalsverige/web',
  'uri' => 'dev.drupalsverige.se',
  'remote-host' => 'dev.drupalsverige.se',
  'remote-user' => 'drupalsverige',
  'path-aliases' => array(
	'%drush' => '/home/drupalsverige/drush',
	'%drush-script' => '/root/drush/drush',
  ),
);

/**
 * This is the alias for your local server.
 * Adjust to you liking.
 */
$aliases['drupal-local'] = array(
  'root' => '/srv/www/drupalsverige/web',
  'uri' => 'local.drupalsverige.se',
);
