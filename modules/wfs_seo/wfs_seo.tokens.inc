<?php
function wfs_seo_token_info(){
  $info = array(
    "types" => array(
      "company" => array(
        "name" => t("Company tokens"),
        "description" => t("Prints company info based on the description"),
      ),
    ),
  );

  include_once("wfs_seo.vars.inc");

  $vars = wfs_seo_variables();

  $social = array(
    'pinterest'   => variable_get('wfs_seo_pinterest',   'https://pinterest.com/'),
    'facebook'    => variable_get('wfs_seo_facebook',    'https://facebook.com/'),
    'google_plus' => variable_get('wfs_seo_google_plus', 'https://plus.google.com/'),
    'twitter'     => variable_get('wfs_seo_twitter',     'https://twitter.com/'),
    'youtube'     => variable_get('wfs_seo_youtube',     'https://youtube.com/channel/'),
    'linked_in'   => variable_get('wfs_seo_linked_in',   'https://linkedin.com/company-beta/'),
    'instagram'   => variable_get('wfs_seo_instagram',   'https://instagram.com/'),
    'houzz'       => variable_get('wfs_seo_houzz',       FALSE),
    'porch'       => variable_get('wfs_seo_porch',       FALSE),
    'angies_list' => variable_get('wfs_seo_angies_list', FALSE),
    'homeadvisor' => variable_get('wfs_seo_homeadvisor', FALSE),
    'yelp'        => variable_get('wfs_seo_yelp',        FALSE),
    'tripadvisor' => variable_get('wfs_seo_tripadvisor', FALSE),
    'foursquare'  => variable_get('wfs_seo_foursquare',  FALSE),
  );

  $vars += $social;
  $vars = array_filter($vars);
  $tokens = array();

  foreach($vars as $k => $v){
    $n = ucwords(str_replace("_", " ", $k));
    $var = variable_get("wfs_seo_$k", $v);
    $tokens[$k] = array(
      "name" => t($n),
      "description" => t("Outputs $n, eg. $var"),
    );
  }

  $info["tokens"]["company"] = $tokens;

  return $info;
}

function wfs_seo_tokens($type, $tokens, array $data = array(), array $options = array()){
  include_once("wfs_seo.vars.inc");

  $vars = wfs_seo_variables();

  $social = array(
    'pinterest'   => variable_get('wfs_seo_pinterest',   'https://pinterest.com/'),
    'facebook'    => variable_get('wfs_seo_facebook',    'https://facebook.com/'),
    'google_plus' => variable_get('wfs_seo_google_plus', 'https://plus.google.com/'),
    'twitter'     => variable_get('wfs_seo_twitter',     'https://twitter.com/'),
    'youtube'     => variable_get('wfs_seo_youtube',     'https://youtube.com/channel/'),
    'linked_in'   => variable_get('wfs_seo_linked_in',   'https://linkedin.com/company-beta/'),
    'instagram'   => variable_get('wfs_seo_instagram',   'https://instagram.com/'),
    'houzz'       => variable_get('wfs_seo_houzz',       FALSE),
    'porch'       => variable_get('wfs_seo_porch',       FALSE),
    'angies_list' => variable_get('wfs_seo_angies_list', FALSE),
    'homeadvisor' => variable_get('wfs_seo_homeadvisor', FALSE),
    'yelp'        => variable_get('wfs_seo_yelp',        FALSE),
    'tripadvisor' => variable_get('wfs_seo_tripadvisor', FALSE),
    'foursquare'  => variable_get('wfs_seo_foursquare',  FALSE),
  );

  $vars += $social;
  $vars = array_filter($vars);

  $replacements = array();

  $sanitize = !empty($options['sanitize']);

  if ($type == 'company') {

    foreach($tokens as $name => $original){
      $val = $vars[$name];
      if($val=="+1-828-"){$val=$vars["phone"];}
      if($name=="street"&&$val==""){$val=$vars["street"];}

      if(isset($social[$name]) && !empty($social[$name])){
        $val = $social[$name];
      }

      $replacements[$original] = $sanitize ? check_plain($val) : $val;
    }

    foreach($vars as $k => $v){
      $n = ucwords(str_replace("_", " ", $k));
      $var = variable_get("wfs_seo_$k", $v);
      if(isset($tokens[$k]) && $var){
        $replacements[$tokens[$k]] = $var;
      }
    }
  }

  return $replacements;
}
