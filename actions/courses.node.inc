<?php
// $Id$
/**
 * @file
 *
 * Handle all custom node related data
 *
 */

/**
 * Implementation of hook_node_info().
 */
function courses_node_info() {
  return array(
    'courses' => array(
      'name' => t('Course'),
      'module' => 'courses',
      'description' => "Create a course.",
      'title_label' => t('Course Name'),
      'body_label' => t('Course Description'),      
    )
  );
} // function courses_node_info()

function courses_form(&$node, $form_state) {
  $type = node_get_types('type', $node);

  // initialize the tab index
  $tabindex = 1;
  
  // initialize the weight index
  $weightindex = -100;
  
  // Fieldset for event information
  $form['courseinformation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Course Information'),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#weight' => $weightindex++,
    '#collapsed' => $openfieldset,
  );
  
  // Display the department for the course
  $form['courseinformation']['coursedept'] = array(
    '#type' => 'textfield',
    '#title' => t('Department'),
    '#description' => t('Enter the department name for the course'),
    '#required' => TRUE,
    '#default_value' => isset($node->coursedept) ? $node->coursedept : variable_get("courses_genericdept", 'Arts and Sciences'),
    '#size' => 10,
    '#maxlength' => 100,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );

  // Define the course title or name
  $form['courseinformation']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Course Name'),
    '#description' => t('Enter the name of the course'),
    '#required' => TRUE,
    '#default_value' => $node->title,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  
  // Display the course number field
  $form['courseinformation']['cnum'] = array(
    '#type' => 'textfield',
    '#title' => t('Course Number'),
    '#description' => t('Enter the number for the course'),
    '#required' => TRUE,
    '#default_value' => isset($node->cnum) ? $node->cnum : '',
    '#size' => 10,
    '#maxlength' => 6,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  
  // Display the course credits field
  $form['courseinformation']['credits'] = array(
    '#type' => 'textfield',
    '#title' => t('Course Credit'),
    '#description' => t('Enter the number of credit hours for the course.'),
    '#required' => FALSE,
    '#default_value' => isset($node->credits) ? $node->credits : '',
    '#size' => 10,
    '#maxlength' => 2,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );  

  // We want the body and filter elements to be adjacent. We could try doing
  // this by setting their weights, but another module might add elements to the
  // form with the same weights and end up between ours. By putting them into a
  // sub-array together, we're able force them to be rendered together.
  $form['courseinformation']['body_filter']['#weight'] = $weightindex++;
  $form['courseinformation']['body_filter']['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Course Description'),
    '#default_value' => $node->body,
    '#required' => FALSE,
    '#rows' => 10,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  $form['courseinformation']['body_filter']['filter'] = filter_form($node->format);

  // Display the type of course
  $form['courseinformation']['coursetype'] = array(
    '#title' => t('Type of Course'),
    '#description' => t('Select the course level or type.'),
    '#type' => 'radios',
    '#default_value' => isset($node->coursetype) ? $node->coursetype : 2,
    '#weight' => $weightindex++,
    '#options' => array(
      '2' => t('Undergraduate'),
      '1' => t('Graduate'),
      '0' => t('Both'),
      ),
    '#attributes' => array('tabindex' => $tabindex++)
  );

  // Display the instructors name
  $form['courseinformation']['instructorname'] = array(
    '#type' => 'textfield',
    '#title' => t('Instructors Name (ie: M. Smith)'),
    '#description' => t('Enter the name of the course instructor.'),
    '#required' => FALSE,
    '#default_value' => isset($node->instructorname) ? $node->instructorname : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  
  // Display the instructors email address
  $form['courseinformation']['instructoremail'] = array(
    '#type' => 'textfield',
    '#title' => t('Instructors Email Address'),
    '#description' => t('Enter the email address of the course instructor.'),
    '#required' => FALSE,
    '#default_value' => isset($node->instructoremail) ? $node->instructoremail : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  
  // Display the call number for the course
  $form['courseinformation']['callnum'] = array(
    '#type' => 'textfield',
    '#title' => t('Call Number'),
    '#description' => t('Enter the call number for the course.'),
    '#required' => FALSE,
    '#default_value' => isset($node->callnum) ? $node->callnum : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );  
  
  // Display the location for the course
  $form['courseinformation']['location'] = array(
    '#type' => 'textfield',
    '#title' => t('Location of Class (ie HH 150)'),
    '#description' => t('Enter the building and room number where the course is being held.'),
    '#required' => FALSE,
    '#default_value' => isset($node->location) ? $node->location : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );  
  
  // Display the days that the course is held
  $form['courseinformation']['daysofweek'] = array(
    '#type' => 'textfield',
    '#title' => t('Days on which class is to meet (M T W R F)'),
    '#description' => t('Enter the days that the course is held.'),
    '#required' => FALSE,
    '#default_value' => isset($node->daysofweek) ? $node->daysofweek : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  
  // Display the times that the course is held
  $form['courseinformation']['timeofday'] = array(
    '#type' => 'textfield',
    '#title' => t('Class Hour(s) (ie 8:00-11:48)'),
    '#description' => t('Enter the times that the course is held.'),
    '#required' => FALSE,
    '#default_value' => isset($node->timeofday) ? $node->timeofday : '',
    '#size' => 10,
    '#maxlength' => 50,
    '#weight' => $weightindex++,
    '#attributes' => array('tabindex' => $tabindex++)
  );  

  // Grab the current quarter and year
  $tempqy = courses_getquarter();
  $curquarter = drupal_substr($tempqy, 0, 2);
  $curyear = drupal_substr($tempqy, 2, drupal_strlen($tempqy));
  
  // Display the quarter
  $form['courseinformation']['quarter'] = array(
    '#title' => t('Quarter'),
    '#description' => t('Select the quarter.'),
    '#type' => 'select',
    '#default_value' => isset($node->quarter) ? $node->quarter : $curquarter,
    '#weight' => $weightindex++,
    '#options' => array(
      'AU' => t('AU'),
      'WI' => t('WI'),
      'SP' => t('SP'),
      'SU' => t('SU'),
      ),
    '#attributes' => array('tabindex' => $tabindex++)
  );
    
  // Generate the years
  $yearstart = date('Y') - 5;
  for ($i=0; $i <= 10; $i++) {
    $options[$yearstart + $i] = t($yearstart + $i);
  }
  
  // Display the year
  $form['courseinformation']['year'] = array(
    '#title' => t('Year'),
    '#description' => t('Select the year.'),
    '#type' => 'select',
    '#default_value' => isset($node->year) ? $node->year : $curyear,
    '#weight' => $weightindex++,
    '#options' => $options,
    '#attributes' => array('tabindex' => $tabindex++)
  );
  unset($options);

  // reset the tab index
  $_SESSION['tabindex'] = 1;
  
  // reset the weight index
  $_SESSION['weightindex'] = 0;  

  return $form;
} // function courses_form(&$node)

/**
 *
 * Implementation of hook_validate().
 *
 * Validate the form input
 */
function courses_validate(&$node) {
  
  // Validate cnum
  if ($node->cnum) { // Is cnum define? (YES)
  
    if (!is_numeric($node->cnum)) { // Is the value not a number? (YES)
      form_set_error('cnum', t('The Course Number must be a number.'));
    } // Is the value not a number? (END)
    
    if (!is_numeric($node->credits)) { // Is the value not a number? (YES)
      form_set_error('credits', t('Course Credit must be a number.'));
    } // Is the value not a number? (END)    
    
  } // Is cnum define? (END)
  
} // function courses_validate(&$node)

/**
 * Implementation of hook_insert().
 *
 * As a new node is being inserted into the database, we need to do our own
 * database inserts.
 */
function courses_insert($node) {
  
  // Insert the custom form data
  db_query("
    INSERT INTO {courses} (
      vid, nid, coursedept, cnum, credits, coursetype, instructorname, instructoremail, callnum, location, daysofweek, timeofday, quarter, year
    ) 
    VALUES (
      %d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'
    )", 
    $node->vid, $node->nid, $node->coursedept, $node->cnum, $node->credits, $node->coursetype, $node->instructorname, $node->instructoremail, $node->callnum, $node->location, $node->daysofweek, $node->timeofday, $node->quarter, $node->year
  );
  
} // function courses_insert($node)

/**
 * Implementation of hook_update().
 *
 * As an existing node is being updated in the database, we need to do our own
 * database updates.
 */
function courses_update($node) {
  // if this is a new node or we're adding a new revision,
  if ($node->revision) { // Is this a revision? (YES)
    
    // Update the node
    courses_insert($node);
    
  }
  else { // Is this a revision? (NO, a new node)
  
    // Insert the new data
    db_query("
      UPDATE {courses} 
      SET
      coursedept = '%s',
      cnum = '%s',
      credits = '%s',
      coursetype = '%s',
      instructorname = '%s',
      instructoremail = '%s',
      callnum = '%s',
      location = '%s',
      daysofweek = '%s',
      timeofday = '%s',
      quarter = '%s',
      year = '%s'
      WHERE 
      vid = %d
    ", 
      $node->coursedept, $node->cnum, $node->credits, $node->coursetype, $node->instructorname, $node->instructoremail, $node->callnum, $node->location, $node->daysofweek, $node->timeofday, $node->quarter, $node->year, $node->vid
    );
    
  } // Is this a revision? (END)
} // function courses_update($node)

/**
 * Implementation of hook_nodeapi().
 *
 * When a node revision is deleted, we need to remove the corresponding record
 * from our table. The only way to handle revision deletion is by implementing
 * hook_nodeapi().
 */
function courses_nodeapi(&$node, $op, $teaser, $page) {
  
  switch ($op) { // Check for the operation being performed
    case 'delete revision': // start case: We are deleting
      // Notice that we're matching a single revision based on the node's vid.
      // Delete the revision data
      db_query('
        DELETE FROM {courses} 
        WHERE vid = %d
      ', 
        $node->vid
      );
      break; // end case: We are deleting
  } // Check for the operation being performed
  
} // function courses_nodeapi(&$node, $op, $teaser, $page)

/**
 * Implementation of hook_delete().
 *
 * When a node is deleted, we need to remove all related records from out table.
 */
function courses_delete($node) {
  // Notice that we're matching all revision, by using the node's nid.
  // Delete the node data
  db_query('
    DELETE FROM {courses} 
    WHERE nid = %d
  ', 
    $node->nid
  );
} // function courses_delete($node)

/**
 * Implementation of hook_load().
 *
 * Now that we've defined how to manage the node data in the database, we
 * need to tell Drupal how to get the node back out. This hook is called
 * every time a node is loaded, and allows us to do some loading of our own.
 */
function courses_load($node) {
  
  // Query the custom data
  $additions = db_fetch_object(db_query('
    SELECT coursedept, cnum, credits, coursetype, instructorname, instructoremail, callnum, location, daysofweek, timeofday, quarter, year
    FROM {courses} 
    WHERE vid = %d
  ', 
    $node->vid
  ));
  
  // Return the query
  return $additions;
} // function courses_load($node)

/**
 * Implementation of hook_view().
 *
 * This is a typical implementation that simply runs the node text through
 * the output filters.
 */
function courses_view($node, $teaser = FALSE, $page = FALSE) {
  
  // Prepare and build the node
  $node = node_prepare($node, $teaser);
  
  // Clear the body because we will manually display it
  $node->content['body'] = array(
    '#value' => '',
    '#weight' => 0,
  );
  
  // Filter the data
  $node->content['myfield'] = array(
    '#value' => theme('courses_customdisplay', $node),
    '#weight' => 1,
  );

  // Return the sanitized node
  return $node;
} // function courses_view($node, $teaser = FALSE, $page = FALSE)

/**
 * Implementation of hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function courses_theme() {
  // Return the node to the theme
  return array(
    'courses_customdisplay' => array(
      'arguments' => array('node'),
    ),
  );
} // function courses_theme()

/**
 * A custom theme function.
 *
 * By using this function to format our node-specific information, themes
 * can override this presentation if they wish. We also wrap the default
 * presentation in a CSS class that is prefixed by the module name. This
 * way, style sheets can modify the output without requiring theme code.
 */
function theme_courses_customdisplay($node) {
  
  // Define our page title
  drupal_set_title(check_plain($node->coursedept) . ' ' . check_plain($node->cnum));
  
  // Initialize our output variable
  $output = '';
  
  // Display the custom node data
  $output .= '<div class="courses_customdisplay">';
  
  // Display the Course Department
  $output .= '<div class="courses_nodedisplay_coursedept">';
  $output .= t('%coursedept&nbsp;', array('%coursedept' => check_plain($node->coursedept)));
  $output .= '</div>';  
  
  // Display the Course Number
  $output .= '<div class="courses_nodedisplay_cnum">';
  $output .= t('%cnum', array('%cnum' => check_plain($node->cnum)));
  $output .= '</div>';
  
  $output .= '<div class="courses_nodedisplay_information">';
  
  // Display the Course Title
  $output .= '<div class="courses_nodedisplay_coursetitle">';
  $output .= t('%title', array('%title' => check_plain($node->title)));
  $output .= '</div>';  
  
  // Display the Instructor Name
  if ($node->instructorname != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_instructorname">';
    $output .= t('Instructor: %instructorname&nbsp;', array('%instructorname' => check_plain($node->instructorname)));
    $output .= '</div>';
  } // Is the field populated? (END)

  // Display the Instructor Name Email Address
  if ($node->instructoremail != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_instructoremail">';
    $output .= t('(Email: %instructoremail)', array('%instructoremail' => check_plain($node->instructoremail)));
    $output .= '</div>';
  } // Is the field populated? (END)
  
  // Display the Course Title
  $output .= '<div class="courses_nodedisplay_body">';
  $output .= t('<strong>Course Description</strong>: !body', array('!body' => t($node->body)));
  $output .= '</div>';    
  
  // Display the Course Type
  $output .= '<div class="courses_nodedisplay_coursetype">';
  
  // Get the course type
  if (check_plain($node->coursetype) == 2) { // Is this an Undergraduate course? (YES)
    $coursetype = 'Undergraduate';
  }
  elseif (check_plain($node->coursetype) == 1) { // Is this an Undergraduate course? (NO, graduate)
    $coursetype = 'Graduate';
  }
  else { // Is this an Undergraduate course? (NO, both)
    $coursetype = 'Undergraduate and Graduate';
  } // Is this an Undergraduate course? (END)
  
  $output .= t('<strong>Course Type</strong>: %coursetype', array('%coursetype' => check_plain($coursetype)));
  $output .= '</div>';
  
  // Display the credits
  if ($node->credits != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_credits">';
    $output .= t('<strong>Course Credits</strong>: %credits', array('%credits' => check_plain($node->credits)));
    $output .= '</div>';
  } // Is the field populated? (END)
  
  // Display the Course Call Number
  if ($node->callnum != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_callnum">';
    $output .= t('<strong>Course Call Number</strong>: %callnum', array('%callnum' => check_plain($node->callnum)));
    $output .= '</div>';
  } // Is the field populated? (END)
  
  // Display the Course Location
  if ($node->location != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_location">';
    $output .= t('<strong>Course Location</strong>: %location', array('%location' => check_plain($node->location)));
    $output .= '</div>';
  } // Is the field populated? (END)
  
  // Display the Days on which class is to meet
  if ($node->daysofweek != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_daysofweek">';
    $output .= t('<strong>Days on which class is to meet</strong>: %daysofweek', array('%daysofweek' => check_plain($node->daysofweek)));
    $output .= '</div>';
  } // Is the field populated? (END)
  
  // Display the Class Hours
  if ($node->timeofday != '') { // Is the field populated? (YES)
    $output .= '<div class="courses_nodedisplay_timeofday">';
    $output .= t('<strong>Class Hour(s)</strong>: %timeofday', array('%timeofday' => check_plain($node->timeofday)));
    $output .= '</div>';
  } // Is the field populated? (END)

  // Display the Quarter
  $output .= '<div class="courses_nodedisplay_quarter">';
  $output .= t('<strong>Quarter</strong>: %quarter', array('%quarter' => check_plain($node->quarter)));
  $output .= '</div>';
  
  // Display the Year
  $output .= '<div class="courses_nodedisplay_year">';
  $output .= t('<strong>Year</strong>: %year', array('%year' => check_plain($node->year)));
  $output .= '</div>';

  $output .= '</div>';

  // End custom node data
  $output .= '</div>';
  
  // Return the output
  return $output;
} // function theme_courses_customdisplay($node)

/**
 *
 * AJAX form handler.
 *
 * Takes care of fetching the generated form from the cache, processing of the submit handlers and rebuilding it
 * Not module dependant code, can be used in any form
 */
function album_ajax_form_handler($delta = 0) {
  // The form is generated in an include file which we need to include manually.
  include_once 'modules/node/node.pages.inc';
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];

  // Get the form from the cache.
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);

  // We need to process the form, prepare for that by setting a few internals.
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  // Set up our form state variable, needed for removing tracks.
  $form_state['remove_delta'] = $delta;

  // Build, validate and if possible, submit the form.
  drupal_process_form($form_id, $form, $form_state);

  // If validation fails, force form submission - this is my own "hack" for overcoming
  // issues where all required fields need to be filled out before the 'add more' button
  // can be clicked.  A better solution is being worked on in Drupal's issue queue.
  if (form_get_errors()) {
    form_execute_handlers('submit', $form, $form_state);
  }

  // This call recreates the form relying solely on the form_state that the
  // drupal_process_form set up.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Return the form
  return $form;
} // function album_ajax_form_handler($delta = 0)