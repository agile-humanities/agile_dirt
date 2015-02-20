<?php

/**
 * @file
 * Theming and preprocessing functions.
 */

/**
 * Implements hook_preprocess().
 */
function ah_dirt_preprocess_dirt_dhcommons_item(array &$variables) {
  $path = drupal_get_path('module', 'ah_dirt');
  drupal_add_css("$path/css/dirt_dhcommons.css");
  $base = variable_get('ah_dirt_dhcommons_url', 'http://dev.dhcommons.org');
  $title = $variables['title'];
  $nid = $variables['nid'];
  $variables['link'] = l($title, "$base/node/$nid");
}

/**
 * Implements hook_preprocess().
 */
function ah_dirt_preprocess_dirt_dhcommons_block(array &$variables) {
  $max_count = variable_get('ah_dirt_project_count', 5);
  $path = drupal_get_path('module', 'ah_dirt');
  drupal_add_css("$path/css/dhcommons_dirt.css");
  $objects = $variables['objects'];
  $project_links = array();
  $site = variable_get('ah_dirt_dhcommons_site_name', 'DHCommons');
  $title = $variables['title'];
  $variables['intro'] = t('The following projects on @site use @tool.', array('@site' => $site, '@tool' => $title));
  foreach ($objects as $object) {
    foreach ($object as $key => $value) {
      $converted_object[$key] = $value;
    }
    $project_links[] = theme('dirt_dhcommons_item', $converted_object);
  }
  $variables['project_links'] = $project_links;
  $count = count($project_links);
  $shown = $count;
  if ($count > $max_count) {
    $variables['projects_links'] = array_slice($project_links, 0, $max_count);
    $shown = $max_count;
  }
  $variables['overflow'] = '';
  $variables['count'] = '';
  if ($shown < $count) {
    $variables['count'] = t("Showing @sub of @all", array('@sub' => $shown, '@all' => $count));
  }
  $site_name = variable_get('ah_dirt_dhcommons_site_name', 'DHCommons');
  $site_url = variable_get('ah_dirt_dhcommons_url', 'http://dhcommons.org') . "/tools/$title";
  $variables['overflow'] = l(t("See all @all on @sitename", array('@all' => $count, '@sitename' => $site_name)), $site_url);
}
