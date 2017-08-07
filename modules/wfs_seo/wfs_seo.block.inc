<?php

function wfs_seo_block_info(){
  $blocks['socials']['info'] = t('White Fox Social Icons');
  $blocks['nap']['info'] = t('White Fox Contact Us/NAP');

  return $blocks;
}

function wfs_seo_block_configure($delta = ''){
  $form = array();

  switch($delta){
    case 'socials':
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

      $pre = 'wfs_seo_social_block_';

      $info = array(
        'pinterest' => array(
          'enabled' => variable_get($pre.'pinterest_enabled', ($social['pinterest']) ? 1 : FALSE),
          'title' => variable_get($pre.'pinterest_title', 'Pinterest'),
          'link' => $social['pinterest'],
          'icon' => variable_get($pre.'pinterest_icon', 'wfa-pinterest'),
        ),
      );

      foreach($social as $key => $value){
        $info[$key] = array(
          'enabled' => variable_get($pre.$key.'_enabled', ($value) ? 1 : FALSE),

          'title' => variable_get($pre.$key.'_title', ucwords(str_replace(array(
            '_plus',
            'angies_list',
            'youtube',
            'linked_in',
            'homeadvisor',
            'tripadvisor',
            'foursquare',
          ), array(
            '+',
            "Angie's List",
            "YouTube",
            "LinkedIn",
            'HomeAdvisor',
            'TripAdvisor',
            'FourSquare',
          ), $key))),

          'icon' => variable_get($pre.$key.'_icon', str_replace(array('linked_in', '_'), array('linkedin', '-'), $key))
        );

        $group = &$form[$key];

        $group = array(
          '#type' => 'fieldset',
          '#title' => t($info[$key]['title']),
        );

        foreach($info[$key] as $k => $v){
          $group[$pre.$key.'_'.$k] = array(
            '#type'          => 'textfield',
            '#title'         => ucwords($k),
            '#default_value' => $v,
          );
        }

        $group[$pre.$key.'_enabled']['#type'] = 'checkbox';

        $group['wfs_seo_'.$key] = array(
          '#type'          => 'textfield',
          '#title'         => $info[$key]['title'],
          '#default_value' => $value,
        );
      }
      break;

    case 'nap':
      $pre = 'wfs_seo_nap_block_';

      $name   = variable_get('wfs_seo_name', variable_get('site_name', FALSE));

      $street = variable_get('wfs_seo_street', FALSE);
      $city   = variable_get('wfs_seo_city', FALSE);
      $state  = variable_get('wfs_seo_state', FALSE);
      $zip    = variable_get('wfs_seo_zip', FALSE);

      $phone  = variable_get('wfs_seo_phone', FALSE);

      $email  = variable_get('wfs_seo_email', variable_get('site_mail', FALSE));

      $form['name'] = array(
        '#type' => 'fieldset',
        '#title' => 'Name',
      );

      $form['address'] = array(
        '#type' => 'fieldset',
        '#title' => 'Address',
      );

      $form['address']['street'] = array(
        '#type' => 'fieldset',
        '#title' => 'Street',
      );

      $form['address']['city'] = array(
        '#type' => 'fieldset',
        '#title' => 'City',
      );

      $form['address']['state'] = array(
        '#type' => 'fieldset',
        '#title' => 'State',
      );

      $form['address']['zip'] = array(
        '#type' => 'fieldset',
        '#title' => 'Zip',
      );

      $form['phone'] = array(
        '#type' => 'fieldset',
        '#title' => 'Phone',
      );

      $form['email'] = array(
        '#type' => 'fieldset',
        '#title' => 'Email',
      );

      $form['name'][$pre.'name_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show name',
        '#default_value' => variable_get($pre.'name_enabled', ($name) ? 1 : FALSE),
      );

      $form['name'][$pre.'name_link'] = array(
        '#type' => 'textfield',
        '#title' => 'Name link',
        '#default_value' => variable_get($pre.'name_link', '/'),
      );

      $form['name']['wfs_seo_name'] = array(
        '#type' => 'textfield',
        '#title' => 'Name',
        '#default_value' => $name,
      );

      $form['address'][$pre.'address_link'] = array(
        '#type' => 'textfield',
        '#title' => 'Address link',
        '#default_value' => variable_get($pre.'address_link', FALSE),
      );

      $form['address']['street'][$pre.'street_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show Street',
        '#default_value' => variable_get($pre.'street_enabled', ($street) ? 1 : FALSE),
      );

      $form['address']['street']['wfs_seo_street'] = array(
        '#type' => 'textfield',
        '#title' => 'Street',
        '#default_value' => $street,
      );

      $form['address']['city'][$pre.'city_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show City',
        '#default_value' => variable_get($pre.'city_enabled', ($city) ? 1 : FALSE),
      );

      $form['address']['city']['wfs_seo_city'] = array(
        '#type' => 'textfield',
        '#title' => 'City',
        '#default_value' => $city,
      );

      $form['address']['state'][$pre.'state_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show state',
        '#default_value' => variable_get($pre.'state_enabled', ($state) ? 1 : FALSE),
      );

      $form['address']['state']['wfs_seo_state'] = array(
        '#type' => 'textfield',
        '#title' => 'State',
        '#default_value' => $state,
      );

      $form['address']['zip'][$pre.'zip_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show zip',
        '#default_value' => variable_get($pre.'zip_enabled', ($zip) ? 1 : FALSE),
      );

      $form['address']['zip']['wfs_seo_zip'] = array(
        '#type' => 'textfield',
        '#title' => 'Zip',
        '#default_value' => $zip,
      );

      $form['phone'][$pre.'phone_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show phone',
        '#default_value' => variable_get($pre.'phone_enabled', ($phone) ? 1 : FALSE),
      );

      $form['phone']['wfs_seo_phone'] = array(
        '#type' => 'textfield',
        '#title' => 'Phone',
        '#default_value' => $phone,
      );

      $form['email'][$pre.'email_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => 'Show email',
        '#default_value' => variable_get($pre.'email_enabled', ($email) ? 1 : FALSE),
      );

      $form['email']['wfs_seo_email'] = array(
        '#type' => 'textfield',
        '#title' => 'Email',
        '#default_value' => $email,
      );
      break;
  }

  return $form;
}

function wfs_seo_block_save($delta = '', $edit = array()){
  $pre = 'wfs_seo_';

  switch($delta){
    case 'socials':

      $social = array(
        'pinterest',
        'facebook',
        'google_plus',
        'twitter',
        'youtube',
        'linked_in',
        'instagram',
        'houzz',
        'porch',
        'angies_list',
        'homeadvisor',
        'yelp',
        'tripadvisor',
        'foursquare',
      );

      foreach($social as $val){
        $field = $pre.$val;

        variable_set($field, $edit[$field]);

        foreach(array('enabled', 'title', 'icon') as $value){
          $field = $pre.'social_block_'.$val.'_'.$value;

          variable_set($field, $edit[$field]);
        }
      }
      break;

    case 'nap':
      $nap = array('name', 'address', 'street', 'city', 'state', 'zip', 'phone', 'email');

      foreach($nap as $val){
        $field = $pre.$val;

        if(isset($edit[$field])){variable_set($field, $edit[$field]);}

        foreach(array('enabled', 'link') as $value){
          $field = $pre.'nap_block_'.$val.'_'.$value;

          if(isset($edit[$field])){variable_set($field, $edit[$field]);}
        }
      }
      break;
  }
}

function wfs_seo_block_view($delta = ''){
  $block = array();

  switch($delta){
    case 'socials':
      $block['subject'] = t('');

      $block['content']['#markup'] = theme('wfs_seo_socials_block');
      $block['content']['#attached']['css'] = array(
        drupal_get_path('module', 'wfs_seo').'/icons/css/icons.css',
        drupal_get_path('module', 'wfs_seo').'/icons/css/color.css'
      );
      break;

    case 'nap':
      $block['subject'] = t('');

      $block['content']['#markup'] = theme('wfs_seo_nap_block');
      $block['content']['#attached']['css'] = array(
        '//maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css',
        drupal_get_path('module', 'wfs_seo').'/css/wfs_seo-nap.css'
      );
      break;
  }

  return $block;
}

function wfs_seo_theme(){
  return array(
    'wfs_seo_socials_block' => array(
      'template' => 'wfs_seo_block_socials',
    ),
    'wfs_seo_nap_block' => array(
      'template' => 'wfs_seo_block_nap',
    ),
  );
}
