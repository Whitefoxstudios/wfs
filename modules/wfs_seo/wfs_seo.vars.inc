<?php
function wfs_seo_vars(){
  global $base_url;

  $pre = "wfs_seo_";

  $theme_default = variable_get('theme_default', FALSE);
  $logo = theme_get_setting("logo", $theme_default);
  $logo_url = file_create_url($logo);

  $sameas = array();

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
    'blogger'     => variable_get('wfs_seo_blogger',     FALSE),
    'tumblr'      => variable_get('wfs_seo_tumblr',      FALSE),
    'wordpress'   => variable_get('wfs_seo_wordpress',   FALSE),
    'flickr'      => variable_get('wfs_seo_flickr',   FALSE),
  );

  foreach($social as $url){
    if($url){$sameas[] = $url;}
  }

  $vars = array(
    "company" => array(
      "@context" => "http://schema.org",
      "@type" => "LocalBusiness",
      "@id" => variable_get($pre."id", ($GLOBALS['base_url'] && !$GLOBALS['base_url'] == 'default')? $GLOBALS['base_url'] : url('/', array('absolute', TRUE))),

      "name" => variable_get($pre."name", variable_get("site_name", FALSE)),

      "address" => array(
        "@type" => "postalAddress",
        "addressLocality" => variable_get($pre."city", FALSE),
        "addressRegion"   => variable_get($pre."state", FALSE),
        "streetAddress"   => variable_get($pre."street", FALSE),
        "postalCode"      => variable_get($pre."zip", FALSE),
      ),

      "geo" => array(
        "@type" => "geoCoordinates",
        "latitude" => variable_get($pre."lat", FALSE),
        "longitude" => variable_get($pre."long", FALSE),
      ),

      "telephone" => variable_get($pre."phone", FALSE),

      "url" => variable_get($pre."url", $base_url),

      "email" => variable_get($pre."email", variable_get("site_mail", FALSE)),

      "openingHours" => variable_get($pre."hours", FALSE),

      "openMonday" => variable_get($pre."openmonday", FALSE),

      "closeMonday" => variable_get($pre."closemonday", FALSE),

      "openTuesday" => variable_get($pre."opentuesday", FALSE),

      "closeTuesday" => variable_get($pre."closetuesday", FALSE),

      "openWednesday" => variable_get($pre."openwednesday", FALSE),

      "closeWednesday" => variable_get($pre."closewednesday", FALSE),

      "openThursday" => variable_get($pre."openthursday", FALSE),

      "closeThursday" => variable_get($pre."closeThursday", FALSE),

      "openFriday" => variable_get($pre."openfriday",  FALSE),

      "closeFriday" => variable_get($pre."closefriday",  FALSE),

      "openSaturday" => variable_get($pre."opensaturday",  FALSE),

      "closeSaturday" => variable_get($pre."closesaturday",  FALSE),

      "openSunday" => variable_get($pre."opensunday",  FALSE),

      "closeSunday" => variable_get($pre."closesunday",  FALSE),

      "logo" => variable_get($pre."logo", $logo_url),

      "sameas" => $sameas
    ),
  );

  $variables = array(
    "wfs_seo_company_json" => json_encode($vars["company"], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES),
  );

  foreach($vars["company"] as $key => $val){
    if($key != 'sameas'){
      $key = str_replace("@", "", $key);

      if(is_array($val)){
        foreach($val as $k => $v){
          $k = str_replace("@", "", $k);

          $variables[$pre.$key."_".$k] = variable_get($pre.$key."_".$k, $v);
        }
      } else {
        $variables[$pre.$key] = variable_get($pre.$key, $val);
      }
    }
  }

  return $variables;
}

function wfs_seo_variables(){
  include_once("wfs_seo.vars.inc");

  $pre = "wfs_seo_";

  $variables = wfs_seo_vars();

  $no_var = array(
    "context",
    "type",
    "address_type",
    "geo_type",
    "company_json",
    "sameas",
  );

  foreach($no_var as $value){
    unset($variables[$pre.$value]);
  }

  $map = array(
    "address_addressLocality" => "city",
    "address_addressRegion" => "state",
    "address_streetAddress" => "street",
    "address_postalCode" => "zip",
    "geo_latitude" => "lat",
    "geo_longitude" => "long",
    "telephone" => "phone",
    "openingHours" => "hours",
  );

  $vars = array();

  foreach($variables as $key => $value){
    $k = str_replace($pre, "", $key);

    if(array_key_exists($k, $map)){
      $k = $map[$k];
    }

    if($k=="telephone"){$k="phone";}

    $value = (!$value) ? variable_get($pre.$k, $value) : $value;

    $vars[$k] = $value;
  }

  $vars["phone"]  = variable_get($pre."phone", FALSE);

  $vars["city"]   = variable_get($pre."city", FALSE);
  $vars["state"]  = variable_get($pre."state", FALSE);
  $vars["street"] = variable_get($pre."street", FALSE);
  $vars["zip"]    = variable_get($pre."zip", FALSE);

  $vars["lat"]    = variable_get($pre."lat", FALSE);
  $vars["long"]   = variable_get($pre."long", FALSE);
  $vars["openMonday"]   = variable_get($pre."openmonday", FALSE);

  $address = t("@street @city, @state @zip", array(
    "@street" => $vars["street"],
    "@city" => $vars["city"],
    "@state" => $vars["state"],
    "@zip" => $vars["zip"],
  ));

  $vars["address"] = variable_get($pre."address", $address);

  $nap = t("@name @address @phone", array(
    "@name" => $vars["name"],
    "@address" => $vars["address"],
    "@phone" => str_replace("+1-", "", $vars["phone"]),
  ));

  $vars["nap"] = variable_get($pre."nap", $nap);

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
    'blogger'     => variable_get('wfs_seo_blogger',     FALSE),
    'tumblr'      => variable_get('wfs_seo_tumblr',      FALSE),
    'wordpress'   => variable_get('wfs_seo_wordpress',   FALSE),
    'flickr'      => variable_get('wfs_seo_flickr',   FALSE),
  );

  $vars += $social;

  foreach($vars as $key => $var){
    if(!$var || empty($var) || $var == ""){
      $var = variable_get($pre.$key, FALSE);
    }

    $vars[$key] = $var;
  }

  if(!$vars['id']){
    $vars['id'] = variable_get($pre."id", (isset($GLOBALS['base_url']) && !empty($GLOBALS['base_url']) && !$GLOBALS['base_url'] == 'default') ? $GLOBALS['base_url'] : url('/', array('absolute', TRUE)));
  }

  return $vars;
}
