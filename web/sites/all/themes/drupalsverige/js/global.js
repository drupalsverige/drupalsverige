$(function() {
	
	/* För två kolumner efter 4 nyheter */
	$(".view-news-listing .view-content .item:gt(3)").addClass("grid-5 smaller");
	$(".grid-5:even").addClass("alpha");
	$(".grid-5:odd").addClass("omega push-1");
	
	$("#search .form-text").focus(function() {
		$("#search label").fadeIn();	
	});

	$("#search .form-text").blur(function() {
		$("#search label").fadeOut();	
	});

	/* Flytta om knapparna för admin och besvara kommentarer*/	
	$(".comment").each(function() {
	
		comment 	= $(this);
		links 		= comment.find("ul.links");
		
		links.remove();
		comment.find(".content").append(links);
		
		$(".content ul.links").css({"position": "absolute", "bottom": 0, "right": 0}).hide();
		
	});
	
	// Ta bort förhandsgranskning
	$('#comment-form #edit-preview').hide();
	
	// Hover för kommentar
	$(".comment .content").hover(function(){
		$(this).find("ul.links").fadeIn("fast");
	}, function() {
		$(this).find("ul.links").fadeOut();
	});

	// Ändra text på "ny"
	$('div#comments .comment .new').text("*").attr("title","Ny");
	
	// Användarlänk
	
	var user = $('#comment-form div div:first');
	var allowedTagsOrg = $('#edit-format-1-wrapper .description ul li:eq(1)').html();
	
	$(user).find('label').remove();
	
	$('#edit-comment').keyup(function() {
		
		if(!$('.preview').length) {
			$('#comments .box').before('<div class="preview comment comment-published last even comment-by-viewer clearfix"><div class="submitted"> '+ Drupal.t("by") + ' ' + user.html() +' - snart.  </div><div class="content">  <p> </p></div> </div>');
		}
		
		if(!$(this).val()) {
			$('.preview').remove();
		} else {
			// $('.preview .content p').html( $(this).val().replace(/<\/?[^>]+>/gi, '') + "<br />" + foo );	
			$('.preview .content p').html( $(this).val() );	
		}
		
	});
	
});

if (Drupal.jsEnabled) {
    $(document).ready(function()
    {
        var lab1 = $('#edit-search-theme-form-1-wrapper label');
        lab1.each(function() { $(this).html($(this).html().replace(":", "")); });
    });
}
