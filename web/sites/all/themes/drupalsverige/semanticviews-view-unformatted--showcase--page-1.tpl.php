<?php
// $Id: semanticviews-view-unformatted.tpl.php,v 1.1.2.3 2009/09/19 22:33:48 bangpound Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php $counter = 0; ?>
<?php if (!empty($title)): ?>
  <<?php print $group_element; ?><?php print drupal_attributes($group_attributes); ?>>
    <?php print $title; ?>
  </<?php print $group_element; ?>>
<?php endif; ?>
<?php if (!empty($list_element)): ?>
  <<?php print $list_element; ?><?php print drupal_attributes($list_attributes); ?>>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <?php if ($counter == 0) { print '<div class="showcase-wrapper"> <div class="showcase-wrapper-inner">';  } ?>
  <?php if (!empty($row_element)): ?>
  <<?php print $row_element; ?><?php print drupal_attributes($row_attributes[$id]); ?>>
  <?php endif; ?>
    <?php print $row; ?>
  <?php if (!empty($row_element)): ?>
  </<?php print $row_element; ?>>
  <?php endif; ?>
  <?php if ($counter == 1) { print '</div> <!-- close showcase wrapper --> </div>'; } $counter ++; if ($counter == 2) { $counter = 0; } ?>
<?php endforeach; ?>
  <?php if ($counter != 2) { print '</div> </div><!-- close showcase wrapper -->'; } ?>
<?php if (!empty($list_element)): ?>
  </<?php print $list_element; ?>>
<?php endif; ?>

