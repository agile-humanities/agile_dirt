<?php

/**
 * Retrieves DHCommons data through REST.
 *
 * @global url $base_url
 *
 * @param string $nitems
 *   number of items to return
 * @param string $tool_name
 *   Name of tool to be returned
 */
function ah_dirt_projects_fetch($title = NULL) {
  global $base_url;
  $url = "$base_url/project";
  $api_key = variable_get('ah_dirt_api_key', '');
  $post_data = array(
    'api-key' => $api_key,
    'tool_name' => $title,
  );
  $data = http_build_query($post_data, '', '&');
  $options = array(
    'headers' => array('Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded'),
    'method' => 'POST',
    'data' => $data
  );
  $response = drupal_http_request($url . '/project/fetch', $options);
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
