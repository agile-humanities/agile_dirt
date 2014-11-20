<?php ?>
<div class ="dhcommons_results_block">
  <ul class ="project_links">
   <?php foreach($variables['project_links'] as $project_link): ?>
    <li class ="project_link"><?php print $project_link; ?></li>
    <?php endforeach; ?>
    </ul>
  <div class ="dhcommons_message"><?php print $overflow; ?></div>
</div>