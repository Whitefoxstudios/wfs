<div class="nap clearfix">
  <ul>
    <?php
      $pre = 'wfs_seo_';
      $preb = $pre.'nap_block_';

      $name = variable_get($pre.'name', variable_get('site_name', FALSE));
      if(variable_get($preb.'name_enabled', ($name) ? 1 : FALSE)){
        $name_link = variable_get($pre.'name_link', '/');

        print "<li><a href='$name_link' rel='home'><span class='fa fa-building'>&nbsp;</span> $name</a></li>";
      }

      $address = '';

      $street = variable_get($pre.'street', FALSE);
      $city   = variable_get($pre.'city', FALSE);
      $state  = variable_get($pre.'state', FALSE);
      $zip    = variable_get($pre.'zip', FALSE);

      if(variable_get($preb.'street_enabled', ($street) ? 1 : FALSE)){
        $address .= $street;
      }

      if(variable_get($preb.'city_enabled', ($city) ? 1 : FALSE)){
        $address .= " $city";
      }

      if(variable_get($preb.'state_enabled', ($state) ? 1 : FALSE)){
        $address .= ", $state";
      }

      if(variable_get($preb.'zip_enabled', ($zip) ? 1 : FALSE)){
        $address .= " $zip";
      }

      if(!empty($address)){
        $address = "<span class='fa fa-location fa-map-marker'>&nbsp;</span> $address";

        $address_link = variable_get($preb.'address_link', FALSE);

        if($address_link){
          $address = "<a href='$address_link' title='Get Directions'>$address</a>";
        }

        print "<li>$address</li>";
      }

      $phone  = variable_get($pre.'phone', FALSE);
      if(variable_get($preb.'phone_enabled', ($phone) ? 1 : FALSE)){
        print "<li><a href='tel:$phone'><span class='fa fa-phone'>&nbsp;</span> $phone</a></li>";
      }

      $email  = variable_get($pre.'email', variable_get('site_mail', FALSE));
      if(variable_get($preb.'email_enabled', ($email) ? 1 : FALSE)){
        print "<li><a href='mailto:$email'><span class='fa fa-envelope-o'>&nbsp;</span> $email</a></li>";
      }
    ?>
  </ul>
</div>