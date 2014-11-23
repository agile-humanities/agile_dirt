<?php

/**
 * Retrieves DHCommons data through REST.
 *
 * @global url $base_url
 *
 * @param string $nitems
 *   number of items to return
 * @param string $tools
 *   Name of tool to be returned
 */
function ah_dirt_projects_fetch($title = NULL) {
  $dhcommons_url = variable_get('ah_dirt_dhcommons_url', 'http://dev.dhcommons.org');
  $rest_path = variable_get('ah_dirt_dhcommons_rest_path', 'rest');
  $alias = variable_get('ah_dirt_dhcommons_alias', 'project');
  $url = "$dhcommons_url/$rest_path/$alias";
  $api_key = variable_get('ah_dhcommons_api_key', '');
  $post_data = array(
    'api-key' => $api_key,
    'tools' => $title,
  );
  $data = http_build_query($post_data, '', '&');
  $options = array(
    'headers' => array('Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded'),
    'method' => 'POST',
    'data' => $data
  );
  $response = drupal_http_request($url . '/fetch', $options);
  $objects = json_decode($response->data);
  $block = theme('dirt_dhcommons_block', array('objects' => $objects));

  return $block;
}

/**
 * Initiates rest call to retrieve projects.
 */
function ah_dirt_get_projects() {
  $path_parts = explode('/', $_GET['q']);
  $node = node_load(end($path_parts));
  return ah_dirt_projects_fetch($node->title);
}