<?php
/**
 * Implements form
 */
function fctl_sf_test_form($form){
   //Get submitted numbers if any
  $result = db_query("SELECT COUNT(num) AS count_num, SUM(num) AS sum_num FROM {fctl_table_two}");
  $records = $result->fetchAssoc();
  $result1 = db_query("SELECT num FROM {fctl_table_two}");
  $records1 = $result1->fetchAll();
  $msg = '';
  if($records['count_num'] > 1){
    foreach($records1 as $row){
      $msg .= $row->num . "+";
    }
    $msg = substr($msg, 0, strlen($msg) - 1) . '=' . $records['sum_num'];
  }elseif($records['count_num'] == 1){
    $msg = $records['sum_num'];
  }
//var_dump ($records1);
  $form = array();
  $form['display'] = array(
    '#type' => 'textfield',
    '#title' => t('Result'),
    '#size'=> 50,
    '#value' => $msg,
  ); 
  $form['test'] = array(
    '#type' => 'textfield',
    '#title' => t('Please enter an Integer between 1 and 30'), 
    '#size'=> 50,
  );
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('fctl_sf_test_form_add_submit'),
    '#validate' => array('fctl_sf_test_form_add_validate'),
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('fctl_sf_test_form_reset_submit'),
    '#validate' => array('fctl_sf_test_form_reset_validate'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit record'),
    '#submit' => array('fctl_sf_form_test_submit'),
  );

  return $form;
}

function fctl_sf_form_test_submit($form, &$form_state){
  global $user;
  $table = 'fctl_table1';
  $record = new stdClass();
  $record->uid = $user->uid;
  $record->date = time();
  $record->message = $form_state['values']['display'];
  dsm($record);
  drupal_write_record($table, $record);
  
  drupal_set_message(t('Thank you for submitting this form!'));
  //Reset fctl_table_two
  $num_deleted = db_delete('fctl_table_two')
    ->execute();
}

/**
 * Implements form_validate.
 */
function fctl_sf_display_form_validate($form, &$form_state){
  //Check if maxumim number of sumissions reached
  $result = db_query("SELECT COUNT(sid) AS count_sub FROM {fctl_table1}");
  $records = $result->fetchAssoc();
  $last = (int)$records['count_sub'];
  if ($last > 30){
    form_set_error('test', 'You have reached the max submissions allowed.');
  }
}

// Submission in table two
function fctl_sf_test_form_add_submit($form, &$form_state){
  $table = 'fctl_table_two';
  $record = new stdClass();
  $record->num = $form_state['values']['test'];
  drupal_write_record($table, $record);
  //  dsm($form);
}

function fctl_sf_test_form_add_validate($form, &$form_state){
  
  //Get the last submission ID
  $result = db_query("SELECT COUNT(num) AS count_num FROM {fctl_table_two}");
  $records = $result->fetchAssoc();
  $last = (int)$records['count_num'];
  if ($last > 10){
   form_set_error('test', 'You have reached the max numbers allowed.');
  }
   //Validate submission value
  $ev = $form_state['values']['test'];
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

/**
 * Reset button
 */
function fctl_sf_test_form_reset_submit(){
  $num_deleted = db_delete('fctl_table_two')
    ->execute();
}

function fctl_sf_test_form_reset_validate(){
  return TRUE;
}