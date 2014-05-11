<?php


$plugin = array(
  'single' => TRUE, 
  'title' => t('HOT Image Pane w/ Caption!'), 
  'description' => t('HOT Image Pane displaying image style based media with a configurable caption'), 
  'category' => t('HotApps!'), 
  'edit form' => 'hot_iac_custom_pane_edit_form', 
  'render callback' => 'hot_iac_custom_pane_render', 
  'admin info' => 'hot_iac_custom_pane_admin_info',
  'defaults' => array( 
    'image1' => '',
    'captiontitle' => '',
    'captiontext' => '',
    'imagestyles' => '',
    'captionbg' => '',
    'captiontitleclass' => '',
    'captiontextclass' => '',
    'captionlayout' => '',
    'captiontitlecolor' => '',
    'captiontextcolor' => '',
    'paddingtop' => '',
    'paddingbottom' => '',
    'paddingleft' => '',
    'paddingright' => '',
    'obheight' => '',
    'obwidth' => '',
  ),
  'all contexts' => TRUE, 
);


/**
 * An edit form for the pane's settings.
 */
function hot_iac_custom_pane_edit_form($form, &$form_state) {
  form_load_include($form_state, 'inc', 'hot_image_and_caption', 'plugins/content_types/hot_iac_custom_pane');
  $conf = $form_state['conf'];
  /*  tweak up panel markup **/
  $form['aligner_start']['#access'] = FALSE;
  $form['aligner_stop']['#access'] = FALSE;
  $form['override_title']['#prefix'] = '<div class="row"><div class="col-md-2 col-sm-2">';
  $form['override_title']['#suffix'] = '</div>';
  $form['override_title_text']['#prefix'] = '<div class="col-md-10 col-sm-10">';
  $form['override_title_text']['#suffix'] = '</div></div>';

  $form['image1'] = array(
    '#type' => 'media',
    '#title' => t('Image'),
    '#description' => t('Image'),
    '#tree' => TRUE,
    '#default_value' => $conf['image1'],
    '#required' => TRUE,
    '#media_options' => array(
      'global' => array(
        'types' => array(
          'image' => 'image',
        ),
      ),
      'schemes' => array(
        'public' => 'public',
      ),
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '100 MB',
      'uri_scheme' => 'public',
    ),
    '#upload_location' => 'public://',
    '#prefix' => '<div class="row hot-ip-top"><div class="col-md-12 col-sm-12"><h4>MEDIA CONFIG</h4></div><div class="col-md-6 col-sm-6">',
    '#suffix' => '</div>',
  );

  $form['imagestyles'] = array(
    '#type' => 'select',
    '#title' => 'Image Style Select',
    '#default_value' => $conf['imagestyles'],
    '#options' => hot_image_and_caption_features_export_options(),
    '#description' => t('Select Image Style for the uploaded image'),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-6 col-sm-6">',
    '#suffix' => '</div></div>',
  );

  $form['captiontitleclass'] = array(
    '#type' => 'select',
    '#title' => 'Caption Title Class',
    '#default_value' => $conf['captiontitleclass'],
    '#options' =>  drupal_map_assoc(array(t('h1'), t('h2'), t('h3'), t('h4'), t('h5'), t('h6'))),
    '#description' => t('Select Caption Title Class'),
    '#required' => TRUE,
    '#prefix' => '<div class="row hot-ip-middle"><div class="col-md-12 col-sm-12"><h4>CAPTION CONFIG</h4></div><div class="col-md-2 col-sm-2">',
    '#suffix' => '</div>',
  );

  $form['captiontitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption Header Text'),
    '#description' => t('The Header Text for the Caption'),
    '#default_value' => $conf['captiontitle'],
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-10 col-sm-10">',
    '#suffix' => '</div></div>',
  );

  $form['captiontextclass'] = array(
    '#type' => 'select',
    '#title' => 'Caption Text Class',
    '#default_value' => $conf['captiontextclass'],
    '#options' =>  drupal_map_assoc(array(t('p'), t('span'))),
    '#description' => t('Select Caption Title Class'),
    '#required' => TRUE,
    '#prefix' => '<div class="row hot-ip-middle1"><div class="col-md-2 col-sm-2">',
    '#suffix' => '</div>',
  );

  $form['captiontext'] = array(
    '#type' => 'textarea',
    '#title' => t('Caption Text'),
    '#description' => t('The Text for the Caption'),
    '#default_value' => $conf['captiontext'],
    '#required' => TRUE,
    '#wysiwyg' => FALSE,
    '#prefix' => '<div class="col-md-10 col-sm-10">',
    '#suffix' => '</div></div>',
  );

  $form['captionlayout'] = array(
    '#type' => 'select',
    '#title' => 'Caption Layout',
    '#default_value' => $conf['captionlayout'],
    '#options' =>  drupal_map_assoc(array(t('GRID - Left w/ BG'), t('GRID - Right w/ BG'),t('OVERLAY - Left Top'), t('OVERLAY - Left Center'), t('OVERLAY - Left Bottom'), t('OVERLAY - Center Top'),t('OVERLAY - Center'),t('OVERLAY - Center Bottom'),t('OVERLAY - Right Top'), t('OVERLAY - Right Center'), t('OVERLAY - Right Bottom'))),
    '#description' => t('Select Caption Title Class'),
    '#required' => TRUE,
    '#prefix' => '<div class="row hot-ip-bottom"><div class="col-md-12 col-sm-12"><h4>OVERLAY CONFIG</h4></div><div class="col-md-12 col-sm-12">',
    '#suffix' => '</div></div>',
  );

  $form['captionbg'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption Background Color'),
    '#description' => t('Just enter the HTML color of the caption background, make sure to include the #, you can put transparent/full rgb css values for overlays as well'),
    '#default_value' => $conf['captionbg'],
    '#required' => FALSE,
    '#size'=> 12,
    '#prefix' => '<div class="row hot-ip-bottom1"><div class="col-md-4 col-sm-4">',
    '#suffix' => '</div>',
  );

  $form['captiontitlecolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption Title Color'),
    '#description' => t('The HTML color of the caption title, make sure to include the #'),
    '#default_value' => $conf['captiontitlecolor'],
    '#required' => FALSE,
    '#size'=> 12,
    '#prefix' => '<div class="col-md-4 col-sm-4">',
    '#suffix' => '</div>',
  );

  $form['captiontextcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption Text Color'),
    '#description' => t('The HTML color of the caption text, make sure to include the #'),
    '#default_value' => $conf['captiontextcolor'],
    '#required' => FALSE,
    '#size'=> 12,
    '#prefix' => '<div class="col-md-4 col-sm-4">',
    '#suffix' => '</div></div>',
  );

  $form['paddingtop'] = array(
    '#type' => 'textfield',
    '#title' => t('Padding Top'),
    '#description' => t('Enter # with either px or em'),
    '#default_value' => $conf['paddingtop'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="row hot-ip-bottom2"><div class="col-md-3 col-sm-3">',
    '#suffix' => '</div>',
  );

  $form['paddingbottom'] = array(
    '#type' => 'textfield',
    '#title' => t('Padding Bottom'),
    '#description' => t('Enter # with either px or em'),
    '#default_value' => $conf['paddingbottom'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="col-md-3 col-sm-3">',
    '#suffix' => '</div>',
  );

  $form['paddingleft'] = array(
    '#type' => 'textfield',
    '#title' => t('Padding Left'),
    '#description' => t('Enter # with either px or em'),
    '#default_value' => $conf['paddingleft'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="col-md-3 col-sm-3">',
    '#suffix' => '</div>',
  );

  $form['paddingright'] = array(
    '#type' => 'textfield',
    '#title' => t('Padding Right'),
    '#description' => t('Enter # with either px or em'),
    '#default_value' => $conf['paddingright'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="col-md-3 col-sm-3">',
    '#suffix' => '</div></div>',
  );

  $form['obwidth'] = array(
    '#type' => 'textfield',
    '#title' => t('OverLay / Background WIDTH'),
    '#description' => t('OPTIONAL Adjust the width of the Overlay / Background, enter in percetage or px'),
    '#default_value' => $conf['obwidth'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="row hot-ip-bottom3"><div class="col-md-6 col-sm-6">',
    '#suffix' => '</div>',
  );

  $form['obheight'] = array(
    '#type' => 'textfield',
    '#title' => t('OverLay / Background HEIGHT'),
    '#description' => t('OPTIONAL Adjust the height of the Overlay / Background, enter in percetage or px'),
    '#default_value' => $conf['obheight'],
    '#required' => FALSE,
    '#size'=> 8,
    '#prefix' => '<div class="col-md-6 col-sm-6">',
    '#suffix' => '</div></div>',
  );



  if (module_exists('token')) {
    $form[$module]['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form[$module]['token_help']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array($settings->token_type),
    );
  }

  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 * Notice, the magic that automatically does that for you.
 */
function hot_iac_custom_pane_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function hot_iac_custom_pane_render($subtype, $conf, $args, $contexts) {
  $image = $conf['image1']['fid'];
  $file = file_load($image);
  $captiontitle = ctools_context_keyword_substitute($conf['captiontitle'], array(), $contexts);
  $captiontext = ctools_context_keyword_substitute($conf['captiontext'], array(), $contexts);

  if ($conf['obheight'] != '' || $conf['obwidth'] != '') {
    $dimension = '';
    if ($conf['obwidth'] != '') {
      $dimension .= 'width:' . $conf['obwidth'] .';';
    }
    if ($conf['obheight'] != '') {
      $dimension .= 'height:' . $conf['obheight'] .';';
    }
  } else {
    $dimension = FALSE;
  }

  if ($conf['paddingtop'] != ''||$conf['paddingbottom'] != ''||$conf['paddingright'] != ''||$conf['paddingleft'] != '') {
    $padding = '';
    if($conf['paddingtop'] != '') {
      $padding .= 'padding-top:' . $conf['paddingtop'] .';';
    } 
    if($conf['paddingbottom'] != '') {
      $padding .= 'padding-bottom:' . $conf['paddingbottom'] .';';
    } 
    if($conf['paddingleft'] != '') {
      $padding .= 'padding-left:' . $conf['paddingleft'] .';';
    } 
    if($conf['paddingright'] != '') {
      $padding .= 'padding-right:' . $conf['paddingright'] .';';
    }
  } else {
    $padding = FALSE;
  }

  if($conf['captionlayout'] == 'GRID - Left w/ BG') {
    $block = new stdClass();
    $block->title = t('<none>'); // This will be overridden by the user within the panel options.
    $block->content = '<div class="container" id="hot-ip">
                        <div class="row">
                        <div class="col-md-3 col-sm-3 gl" style="background-color:' . $conf['captionbg'] . ';' . $dimension . $padding . '">
                        <' . $conf['captiontitleclass'] . ' style="color:' . $conf['captiontitlecolor'] . '">' . $captiontitle . '</' . $conf['captiontitleclass'] . '>
                        <' . $conf['captiontextclass'] . ' style="color:' . $conf['captiontextcolor'] . '">'. $captiontext . '</' . $conf['captiontextclass'] . '>
                        </div>
                        <div class="col-md-9 col-sm-9 gl-image">
                        <img src="' . image_style_url($conf["imagestyles"],$file->uri) . '" />
                        </div>
                        </div>
                        </div>';

    return $block;
  } elseif($conf['captionlayout'] == 'GRID - Right w/ BG') {
    $block = new stdClass();
    $block->title = t('<none>'); // This will be overridden by the user within the panel options.
    $block->content = '<div class="container" id="hot-ip">
                        <div class="row">
                        <div class="col-md-9 col-sm-9 gr-image">
                        <img src="' . image_style_url($conf["imagestyles"],$file->uri) . '" />
                        </div>
                        <div class="col-md-3 col-sm-3 gr" style="background-color:' . $conf['captionbg'] . ';' . $dimension . $padding . '">
                        <' . $conf['captiontitleclass'] . ' style="color:' . $conf['captiontitlecolor'] . '">' . $captiontitle . '</' . $conf['captiontitleclass'] . '>
                        <' . $conf['captiontextclass'] . ' style="color:' . $conf['captiontextcolor'] . '">'. $captiontext . '</' . $conf['captiontextclass'] . '>
                        </div>
                        </div>
                        </div>';

    return $block;    
  }
}

/**
 * Implements hook_features_export_options().
 * gets the image style for us in a nice list
 */
function hot_image_and_caption_features_export_options() {
  $options = array();
  foreach (image_styles() as $name => $style) {
    $options[$name] = $style['name'];
  }
  return $options;
}
