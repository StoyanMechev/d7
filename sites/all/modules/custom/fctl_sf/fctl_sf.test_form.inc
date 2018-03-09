<?php
/**
 * Test form
 */
//function fctl_sf_test_form_page(){  
//  return drupal_get_form('fctl_sf_test_form');
//}

function fctl_sf_test_form_page (){
  $form = array();
  $form['test'] = array(
    '#type' => 'textfield',
    '#title' => t('Please enter your data'),
    '#description' => t('Field decription'), 
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),  
  );  
  return $form;
}