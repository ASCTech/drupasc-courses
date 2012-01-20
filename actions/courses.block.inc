<?php
// $Id$
/**
 * @file
 *
 * Process block for user interface.
 *
 */

/**
 * Handler for courses display
 */
function courses_userdisp() {
  
  // Initialize the output variable 
  $page_content = '';

  $page_content .= '<div class="courses-list-clear"></div>';

  if (isset($_SESSION['offering']) == 1 && $_SESSION['offering'] == 0) { // Was the current quarter offering selected? (YES)
    // Clear the passed session value
    unset($_SESSION['offering']);    
    // Grab the current quarter and year
    $tempqy = courses_getquarter();
    // Pull the quarter
    $quarter = drupal_substr($tempqy, 0, 2);
    // Pull the year
    $year = drupal_substr($tempqy, 2, drupal_strlen($tempqy));
    // Display the list of courses
    $page_content = courses_displaylist($quarter, $year);
  }
  elseif (isset($_SESSION['offering']) == 1 && $_SESSION['offering'] == 1) {  // Was the current quarter offering selected? (NO, archive)
    // Check for the secondary form
    if (isset($_SESSION['selterm']) == 1 && $_SESSION['selterm'] == 1) { // Has a term been selected? (YES)
      // Get the quarter from the session
      $quarter = $_SESSION['quarter'];
      // Get the year from the session
      $year = $_SESSION['year'];
      // Clear the passed session values
      unset($_SESSION['offering']);
      unset($_SESSION['selterm']);
      unset($_SESSION['quarter']);
      unset($_SESSION['year']);
      // Diplay the list of courses
      $page_content = courses_displaylist($quarter, $year);  
    }
    else {  // Has a term been selected? (NO, display the select term form)
      // get and render the select term form
      $page_content .= drupal_get_form('courses_selterm_form');  
    } // Has a term been selected? (END)  
  }
  else {  // Was the current quarter offering selected? (NO, display the form)
    // get and render the select offerings form
    $page_content .= drupal_get_form('courses_selofferings_form');    
  } // Was the current quarter offering selected? (END)
  
  // Return the output
  return $page_content;  
} // function courses_userdisp()

/**
 * render the select offerings form
 */
function courses_selterm_form($form_state) {
  
  // initialize the tab index
  $_SESSION['tabindex'] = 1;

  // initialize the form array
  $form = array();
  
  // Fieldset for select term fields
  $form['seltermset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select Date'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => 'Use the buttons below to select archived, current or future course offerings.',
  );  
  
  // Select the quarter
  $form['seltermset']['quarter'] = array(
    '#title' => t('Quarter'),
    '#description' => t('Select the quarter.'),
    '#type' => 'select',
    '#default_value' => 'AU',
    '#options' => array(
      'AU' => t('AU'),
      'WI' => t('WI'),
      'SP' => t('SP'),
      'SU' => t('SU'),
      ),
    '#attributes' => array('tabindex' => $_SESSION['tabindex']++),
  );
  
  // Generate the years
  $yearstart = date('Y') - 5;
  for ($i=0; $i <= 10; $i++) {
    $options[$yearstart + $i] = t($yearstart + $i);
  }
  
  // Select the year
  $form['seltermset']['year'] = array(
    '#title' => t('Year'),
    '#description' => t('Select the year.'),
    '#type' => 'select',
    '#default_value' => date('Y'),
    '#options' => $options,
    '#attributes' => array('tabindex' => $_SESSION['tabindex']++),
  );
  unset($options);

  // submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Select Date'),
    '#attributes' => array('tabindex' => $_SESSION['tabindex']++),
  );
  
  // reset the tab index
  $_SESSION['tabindex'] = 1;  
  
  // return the form to be rendered
  return $form;
} // function courses_selterm_form($form_state)

/**
 * submit the select term form
 */
function courses_selterm_form_submit($form, &$form_state) {
  // Define the select term session variables
  $_SESSION['offering'] = 1;
  $_SESSION['selterm'] = 1;
  $_SESSION['quarter'] = $form_state['values']['seltermset']['quarter'];
  $_SESSION['year'] = $form_state['values']['seltermset']['year'];
} // function courses_selofferings_form_submit($form, &$form_state)

/**
 * render the select offerings form
 */
function courses_selofferings_form($form_state) {
  
  // initialize the tab index
  $_SESSION['tabindex'] = 1;

  // initialize the form array
  $form = array();
  
  // Fieldset for offerings fields
  $form['offerset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select One'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => 'Use the buttons below to select archived, current or future course offerings.',
  );
  
  // current course offerings button
  $form['offerset']['current'] = array(
    '#type' => 'submit',
    '#value' => t('Current Course Offerings'),
    '#attributes' => array('tabindex' => $_SESSION['tabindex']++),
    '#suffix' => '<br />',
    '#submit' => array('courses_selofferings_current_form_submit'),
  );
  
  // archived/future offerings button
  $form['offerset']['archive'] = array(
    '#type' => 'submit',
    '#value' => t('Archived/Future Offerings'),
    '#attributes' => array('tabindex' => $_SESSION['tabindex']++),
    '#submit' => array('courses_selofferings_archive_form_submit'),
  );  
  
  // reset the tab index
  $_SESSION['tabindex'] = 1;  
  
  // return the form to be rendered
  return $form;    
} // function courses_selofferings_form($form_state)

/**
 * Submit the select offering form - current selected
 */
function courses_selofferings_current_form_submit($form, &$form_state) {
  // Define the offering session variable
  $_SESSION['offering'] = 0;        
} // function courses_selofferings_current_form_submit($form, &$form_state)

/**
 * Submit the select offering form - archive selected
 */
function courses_selofferings_archive_form_submit($form, &$form_state) {
  // Define the offering session variable
  $_SESSION['offering'] = 1;  
} // function courses_selofferings_archive_form_submit($form, &$form_state)

/**
 * Display list of courses
 */
function courses_displaylist($quarter, $year) {
  
  // prepare the sql for available courses
  $sql = "
  SELECT {node}.nid, {node}.vid, {node}.title, {node_revisions}.body, {courses}.coursedept, {courses}.cnum, {courses}.credits, {courses}.coursetype, {courses}.instructorname, {courses}.instructoremail, {courses}.callnum, {courses}.location, {courses}.daysofweek, {courses}.timeofday, {courses}.quarter, {courses}.year
  FROM {node}
  LEFT JOIN {courses} ON {courses}.nid = {node}.nid
  LEFT JOIN {node_revisions} ON {node_revisions}.vid = {node}.vid
  WHERE 1=1
  ";
  $sql .= "AND quarter = '%s'";
  $sql .= "AND year = '%s'";
  $sql .= "ORDER BY coursedept, cnum";
  
  // prepare the sql to count the available courses
  $countsql = "
  SELECT COUNT({node}.nid)
  FROM {node}
  LEFT JOIN {courses} ON {courses}.nid = {node}.nid
  LEFT JOIN {node_revisions} ON {node_revisions}.vid = {node}.vid
  WHERE 1=1
  ";
  $countsql .= "AND {courses}.quarter = '%s'";
  $countsql .= "AND {courses}.year = '%s'";  
  
  // Run the main query
  $query = db_query($sql, $quarter, $year);
  // Count the results
  $num_rows = db_result(db_query($countsql, $quarter, $year));
  
  // Handle zero results
  if ($num_rows == 0) { // Are there results? (NO)
    // Display a message
    $block_content .= 'No courses were found for ' . $quarter . ' ' . $year;
    $block_content .= '<br /><br />';
    $block_content .= '<a href="' . $_SERVER['REFERRER'] . '" title="Return to the main courses page.">Please try again</a>.';
  }
  else { // Are there results? (YES, display courses)    
    // Display the courses    
    $block_content .= '<div class="courses-list-qyear">' . $quarter . ' ' . $year . '</div>';
    $block_content .= '<div class="courses-list-clear"></div>';
    $block_content .= '<br />';
    $block_content .= '<hr />';
    $block_content .= '<br />';
    // Loop over the courses
    while ($row = db_fetch_object($query)) {    
      $block_content .= '<div class="courses-list-clear"></div>';
      $block_content .= '<div class="courses-list-department">' . $row->coursedept . ' ';
      $block_content .= $row->cnum . ': </div>';
      $block_content .= '<div class="courses-list-title"><a href="node/' . $row->nid . '" title="Details about ' . $row->title . '.">' . $row->title . '</a>';
      if ($row->credits != "") {
        $block_content .= ' (' . $row->credits . ')';
      }
      $block_content .= '</div>';

      if ($row->instructorname != "") {
        $block_content .= '<div class="courses-list-instructorname">';
        $block_content .= 'Instructor: <a href="mailto:' . $row->instructoremail . '" title="Email ' . $row->instructorname . '.">';
        $block_content .= $row->instructorname;
        $block_content .= '</a>';
        $block_content .= '</div>';
      }
      if ($row->instructorname == '') {
        $block_content .= '<br />';
      }
      $block_content .= '<a href="node/' . $row->nid . '" title="Details about ' . $row->title . '.">more in course description...</a>';
      $block_content .= '<br /><br />';
      $block_content .= '<hr />';
      $block_content .= '<br />';
    }  
  } // Are there results? (END)
  
  // return the block content
  return $block_content;
} // function courses_displaylist()