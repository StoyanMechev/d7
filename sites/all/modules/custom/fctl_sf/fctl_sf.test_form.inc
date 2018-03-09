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
    '#type' => 'select',
    '#title' => t('Please enter your data'),
    '#description' => t('Description'), 
    '#options' => array(
      'opt1' => t('Option 1'),
      'opt2' => t('Option 2'),  
    ),
    '#default_value' => 'opt2'  
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),  
  );  
  return $form;
}