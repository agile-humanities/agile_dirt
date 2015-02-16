<?php
/**
 * @file
 * Template for full block.
 */
?>
<div class ="dhcommons_results_block">
  <p class ="dh_commons_intro">
    <?php print $intro; ?>
  </p>

  <ul class ="project_links">
    <?php foreach ($variables['project_links'] as $project_link): ?>
      <li class ="project_link"><?php print $project_link; ?></li>
    <?php endforeach; ?>
  </ul>
  <div class ="dhcommons_message"><?php print $count; ?></div>
  <div class ="dhcommons_message"><?php print $overflow; ?></div>
</div>