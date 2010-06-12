if (Drupal.jsEnabled) {
  Drupal.behaviors.better_exposed_filters = function() {

    /*
     * Add Select all/none links to specified checkboxes
     */
    var selected = $('.form-checkboxes.bef-select-all-none');
    if (selected.length) {
      var selAll = Drupal.t('Select All');
      var selNone = Drupal.t('Select None');
      
      // Set up a prototype link and event handlers
      var link = $('<a class="bef-toggle" href="#">'+ selAll +'</a>')
      link.click(function() {
        if (selAll == $(this).text()) {
          // Select all the checkboxes
          $(this)
            .html(selNone)
            .siblings('.bef-checkboxes')
              .find('.form-item input:checkbox').each(function() {
                $(this).attr('checked', 'checked');
              });
        }
        else {
          // Unselect all the checkboxes
          $(this)
            .html(selAll)
            .siblings('.bef-checkboxes')
              .find('.form-item input:checkbox').each(function() {
                $(this).attr('checked', '');
              });
        }
        return false;
      });

      // Add link to the page for each set of checkboxes.
      selected.each(function(index) {
        // Clone the link prototype and insert into the DOM
        var newLink = link.clone(true);
        newLink.insertBefore($('.bef-checkboxes', this));
        
        // If all checkboxes are already checked by default then switch to Select None
        if ($('input:checkbox:checked', this).length == $('input:checkbox', this).length) {
          newLink.click();
        }
      });
    }
  };
}
