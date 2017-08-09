<div class="social clearfix">
  <ul>
    <?php
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
      );

      $pre = 'wfs_seo_social_block_';

      foreach($social as $key => $val){
        $field = $pre.$key;

        if(variable_get($field.'_enabled', FALSE) && $val){
          $machine_key = str_replace(array('linked_in', '_'), array('linkedin', '-'), $key);
          $color = "$machine_key-color";

          $title = variable_get($field.'_title', ucwords(str_replace(array(
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
          ), $key)));

          $icon = variable_get($field.'_icon', $machine_key);

          print "<li class='$color'><a href='$val' title=\"$title\" class='wf wf-$machine_key'></a></li>";
        }
      }
    ?>
  </ul>
</div>
