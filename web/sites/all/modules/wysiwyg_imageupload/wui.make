api=2
core=6.x

;the current release of wui
projects[]=wysiwyg_imageupload

; or the current development master for testing / development (uncomment to use)
;projects[wysiwyg_imageupload][type] = theme
;projects[wysiwyg_imageupload][download][type] = git
;projects[wysiwyg_imageupload][download][url] = git://github.com/EugenMayer/wysiwyg_imageupload

;drupal
projects[]=drupal

projects[jquery_update][version] = 2.0-alpha1
projects[]=imagecache
projects[]=imageapi 
projects[]=wysiwyg
projects[]=jquery_ui
projects[]=jquery_ui_dialog

; Some extra sauce (optional modules)
projects[] = admin_menu
projects[] = views
projects[] = lightbox2

libraries[jquery.ui][download][type]="get"
libraries[jquery.ui][download][url]="http://jquery-ui.googlecode.com/files/jquery-ui-1.7.3.zip"
libraries[jquery.ui][destination]="modules/jquery_ui/"

libraries[ckeditor][download][type]="get"
libraries[ckeditor][download][url]="http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.4.1/ckeditor_3.4.1.tar.gz"

; Having a second wysiwyg editor is a good idea for testing!
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "http://downloads.sourceforge.net/project/tinymce/TinyMCE/3.2.6/tinymce_3_2_6.zip"