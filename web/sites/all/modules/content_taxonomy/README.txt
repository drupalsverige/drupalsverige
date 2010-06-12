Content Taxonomy:
*****************

This module provides a field type for cck for referencing taxonomy terms.

The content_taxonomy.module implements all basic field functions. 
The other modules offer different widgets (selects,..)

Installation:
-------------
1.  Install this files into the modules directory of your choice (for example, sites/yoursite.com/modules/content_taxonomy).
2.  Enable content_taxonomy.module in the admin/modules page
3.  Enable wanted widgets in admin/modules (e.g. content_taxonomy_select.module) Note: all require content_taxonomy.module!
4.  Optional enable content_taxonomy_views.module for improved taxonomy-views support 

Settings:
---------
For every field you have to select the vocabulary and optional a parent term in the field settings. 
If a parent is selected, only children of this parent will be given to the form, else the whole vocabulary.
Additional you can choose whether the term is saved as a real tag in the term_node table (standard)
or the term is only saved in a cck-table (so not a real term - node connection) 



content_taxonomy_options:
-------------------------
 provides a options widget type
 this includes:
   - radios/checkboxes (depends on single/multiple)
   - multiple/single select field (opt-groups are possible)

content_taxonomy_autocomplete:
------------------------------
 provides autocomplete. synonyms are considered by this autocomplete. Optional you can restrict the
 saving of new terms.

content_taxonomy_activeselect:
------------------------------
 requires the activeselect.module
 offers dependent selects, at the moment 2-3 bars are possible



Author:
-------
Matthias Hutterer
mh86@drupal.org
m_hutterer@hotmail.com
