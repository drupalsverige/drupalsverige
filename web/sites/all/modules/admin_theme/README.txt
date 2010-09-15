/* $Id: README.txt,v 1.1.2.3 2009/08/15 08:17:23 davyvandenbremt Exp $ */

Description
-----------

Drupal allows you to define a different theme for administration pages (Administer -> Site configuration -> Administration theme). By default this only applies to pages with a path starting with 'admin' and content editing pages.

The Administration theme module adds a few more option to the default configuration page like :
- Use administration theme for batch processing
- Use administration theme for code reviews
- ...

Some of these pages will only appear if they apply to your installation, i.e. you have the module installed which generates these pages.

You also have the option to define a custom set of Drupal paths or aliases to apply the administration theme for.


Requirements
------------

This module requires Drupal 6. A Drupal 5 version is available.


Installation
------------

1) Copy/upload the admin_theme module folder to the sites/all/modules
directory of your Drupal installation. 

2) Enable the Administration theme module in Drupal (administer -> modules).


Configuration
-------------

You can enable/disable the administration theme on the administration theme
configuration page.

Administration theme can be configured at : 
  Administer -> Site configuration -> Administration theme
  
Developers
----------
You can add define extra pages where the administration theme should be applied to by implementing the hook_admin_theme_options hook in your modules.
This hook uses an $op variable to specify two operation that can be done: getting all "options" and checking if an option should be applied to a path. Check out admin_theme_admin_theme for an example implementation.


Author
------

Davy Van Den Bremt <info@davyvandenbremt.be>
http://www.davyvandenbremt.be