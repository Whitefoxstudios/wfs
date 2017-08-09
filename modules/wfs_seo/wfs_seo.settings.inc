<?php
function wfs_seo_company_info_form(){
  $pre = "wfs_seo_";

  include_once("wfs_seo.vars.inc");

  $vars = wfs_seo_variables();

  $social = array(
    'pinterest'   => variable_get($pre.'pinterest',   'https://pinterest.com/'),
    'facebook'    => variable_get($pre.'facebook',    'https://facebook.com/'),
    'google_plus' => variable_get($pre.'google_plus', 'https://plus.google.com/'),
    'twitter'     => variable_get($pre.'twitter',     'https://twitter.com/'),
    'youtube'     => variable_get($pre.'youtube',     'https://youtube.com/channel/'),
    'linked_in'   => variable_get($pre.'linked_in',   'https://linkedin.com/company-beta/'),
    'instagram'   => variable_get($pre.'instagram',   'https://instagram.com/'),
    'houzz'       => variable_get($pre.'houzz',       FALSE),
    'porch'       => variable_get($pre.'porch',       FALSE),
    'angies_list' => variable_get($pre.'angies_list', FALSE),
    'homeadvisor' => variable_get($pre.'homeadvisor', FALSE),
    'yelp'        => variable_get($pre.'yelp',        FALSE),
    'tripadvisor' => variable_get($pre.'tripadvisor', FALSE),
    'foursquare'  => variable_get($pre.'foursquare',  FALSE),
    'blogger'     => variable_get($pre.'blogger',     FALSE),
    'tumblr'      => variable_get($pre.'tumblr',      FALSE),
    'wordpress'   => variable_get($pre.'wordpress',   FALSE),
  );

  $vars += $social;

  if(module_exists('geocoder')){
    $point = geocoder('google', $vars["address"]);

    if($point){
      $geoJSON = $point->out('json');
      $geoObject = json_decode($geoJSON);

      $vars["lat"] = $geoObject->coordinates[1];
      $vars["long"] = $geoObject->coordinates[0];
    } else {
      drupal_set_message("didn't geocode ".$vars["address"]);
    }
  }

  foreach($vars as $key => $value){
    if($key == 'sameas'){
      unset($vars[$key]);
    }

    if(!$value || is_null($value) || empty($value) || $value == ""){
      $value = FALSE;
    }

    $title = t(ucwords(str_replace("_", " ", $key)));

    $default_value = variable_get($pre.$key, $value);

    if($key == "logo" && !($default_value)){
      $logo_url = file_create_url(theme_get_setting("logo", variable_get('theme_default', 'jollyness')));

      $default_value = variable_get($pre.$key, $logo_url);
    }

    if($key == "address"){
      $default_value = variable_get($pre.$key, t("@street @city, @state @zip", array(
        "@street" => $vars["street"],
        "@city" => $vars["city"],
        "@state" => $vars["state"],
        "@zip" => $vars["zip"],
      )));
    }

    if($key == "nap"){
      $default_value = variable_get($pre.$key, t("@name @address @phone", array(
        "@name" => $vars["name"],
        "@address" => $vars["address"],
        "@phone" => str_replace("+1-", "", $vars["phone"]),
      )));
    }

    $form[$pre.$key] = array(
      "#type"          => "textfield",
      "#title"         => $title,
      "#default_value" => $default_value,
    );
  }

  $form['wfs_seo_testing'] = array(
    '#markup' => "<pre>".json_encode($vars, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES)."</pre>"
  );

  $form = wfs_seo_form($form);

  $form['actions']['submit']['#value'] = t('Save Company Information');

  return $form;
}

function wfs_seo_form($form) {
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Progress'));

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }

  $form['#submit'][] = 'wfs_seo_form_submit';

  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }

  return $form;
}

function wfs_seo_form_submit($form_id, &$form_state){
  $values = &$form_state['values'];

  wfs_seo_form_walk($values);

  drupal_set_message('Company Info Saved!');
}

function wfs_seo_form_walk($values){
  foreach($values as $key => $value){
    if(is_array($value)){
      wfs_seo_form_walk($value);
    } else {
      variable_set($key, $value);
    }
  }
}
