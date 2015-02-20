<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Retrieves DHCommons data through REST.
 *
 * @global url $base_url
 *
 * @param string $title
 *   Name of project to be returned
 */
function ah_dirt_projects_fetch($title = NULL) {
  $dhcommons_url = variable_get('ah_dirt_dhcommons_url', 'http://dev.dhcommons.org');
  $rest_path = variable_get('ah_dirt_dhcommons_rest_path', 'rest');
  $alias = variable_get('ah_dirt_dhcommons_alias', 'project');
  $url = "$dhcommons_url/$rest_path/$alias";
  $api_key = variable_get('ah_dhcommons_api_key', '');
  $taxonomy = variable_get('ah_dirt_dhcommons_taxonomy', 'tools_used');
  $sort = variable_get('ah_dirt_dhcommons_sort', 'timestamp');
  $post_data = array(
    'api-key' => $api_key,
    'tool_name' => $title,
    'taxonomy' => $taxonomy,
    'sort' => $sort,
  );
  $data = http_build_query($post_data, '', '&');
  $options = array(
    'headers' => array(
      'Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded'),
    'method' => 'POST',
    'data' => $data,
  );
  $response = drupal_http_request($url . '/fetch', $options);
  if (!$response || floor($response->code / 100) != 2) {
    watchdog('agile_dirt', 'Check REST connectivity');
    return;
  }
  $objects = json_decode($response->data);
  if ($objects) {
    return theme('dirt_dhcommons_block', array('objects' => $objects, 'title' => $title));
  }
}

/**
 * Initiates rest call to retrieve projects.
 */
function ah_dirt_get_projects() {
  $query = $_GET['q'];
  $source = drupal_lookup_path("source", $query);
  $path = $source ? $source : $query;
  $node = menu_get_object("node", 1, $path);
  return ah_dirt_projects_fetch($node->title);
}
