// $Id$
/**
 * @author Eugen Mayer (http://kontextwork.de)
 * @Copyright 2010 KontextWork
 */
(function($) {
  $.fn.drupalwiki_imageselect_element = function() {
    return this.each( function(){
      // **************** Init *****************/
      var $parent = $(this);
      var context = $parent.attr('id');
      var container = context+'-container';
      
      if(context === null) {
        alert('cant initialize drupalwiki-imageselect-element: '+context);
        return;
      }
      
      $parent.hide();
      // Lets set all things up.
      insert_container();
      var $container = $('#'+container);      
      insert_values();
      update_selection();
      // we are done, so set us to processed
      $parent.addClass('drupalwiki-imageselect-element-processed');   
      
      // **** our hepler functios *********
      function insert_container() {
	$parent.after('<div id="' + container + '" class="drupalwiki_imageselect_element_container"></div>');
      }
      
      function insert_values() {
	$parent.find('option').each( function() {
	    var key = $(this).val();
	    // we use text so we actually decode what there, so <img> shows up as an image	    
	    $('<span class="select_option" key="'+key+'">'+$(this).text()+'</span>')
	      .bind('click', function() {
		  // set our parents value, so on form submit
		  // the right selection is submitted
		  select_parent_option(key);
		}
	      )
	      .appendTo($container);	    
	  }
	);
      }
      
      function select_parent_option(key) {
	$parent.val(key);
	// update the selection in our special UI
	update_selection();
      }
      
      // updates the selection in the UI according to the parents value
      function update_selection() {	
	var key = $parent.val();
	// clear selections first
	$container.find('span.select_option').removeClass('selected');
	$container.find('span.select_option[key="'+key+'"]').addClass('selected');
      }
    }
    );
  }
})(jQuery);