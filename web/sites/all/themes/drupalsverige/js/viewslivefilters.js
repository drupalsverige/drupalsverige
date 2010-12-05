Drupal.behaviors.viewsLiveFilters = function() {
  $('.view-provider .view-filters form:not(.viewsLiveFilters-processed), .view-showcase .view-filters form:not(.viewsLiveFilters-processed)').each(function() {
    var form = this;
    var timeout = undefined;
    var delay = 1000;

    // Remove form's submit button.
    $(':submit, .submit-button', form).hide();

    // Submit form immediately when a form element's value changes.

    $('.views-exposed-widget .form-item select', form).bind('change', function() {
      $(form).submit();
    });

    $('.views-exposed-widget .form-item input:checkbox', this).bind('click', function() {
      $(form).submit();
    });

  }).addClass('viewsLiveFilters-processed');
}