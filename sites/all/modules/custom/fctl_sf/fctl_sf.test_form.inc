<?php
/**
 * Define some variables
 */
$count_numbers = 0;
$msg = '';
/**
 * Test form
 */
function fctl_sf_test_form(){
  $form = array();
  $form['test'] = array(
    '#type' => 'textfield',
    '#title' => t('Please enter number between 1 and 30'),
    '#description' => t('Integer between 1 and 30'), 
    '#required' => TRUE,
    '#element_validate' => array('fctl_form_field_validate'),
    '#markup' => 'Markup TEXT',
  );
  $form['buttons']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit data'),
  );
  
  return $form;
}

function fctl_sf_test_form_submit($form, &$form_state){
 // dsm($form_state['values']);
  global $user;
  $table = 'fctl_table1';
  $record = new stdClass();
  $record->uid = $user->uid;
  $record->date = time();
  $record->message = $form_state['values']['test'];
 // dsm($record);
  drupal_write_record($table, $record);
  watchdog('fctl_sf', 'Record added');
  
  drupal_set_message(t('Thank you for submitting this form!'));
}

/**
 * 
 * @param type $form
 * @param type $form_state
 */
function fctl_sf_test_form_validate($form, &$form_state){
 // dpm($form);
 // form_set_error('title', 'Title cannot be "test"');
}

/**
 * 
 */
function fctl_form_field_validate($element, &$form_state){
  //dpm($element);
 // print_r($element);
  $ev = $element['#value'];
  print 'EV = ' . $ev;
  if (!is_numeric($ev)){
    form_set_error('test', 'Please enter a number.');
    return;
  }
  elseif (strpos($ev,'.') || strpos($ev,',')){
    form_set_error('test', 'Please enter an integer number.');
    return;
  }
  $ev = (int)$ev;
  if ($ev < 1 || $ev > 30){
    form_set_error('test', 'Please enter a number between 1 and 30.');
    return;
  }
}