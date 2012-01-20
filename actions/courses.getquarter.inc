<?php
// $Id$
/**
 * @file
 *
 * Get the current quarter. Must be manually updated.
 *
 */

/**
 * Get the current quarter
 */
function courses_getquarter() {
  
  // Create the current date, use mktime so we can perform calculations on the date
  $tempmonth = date('n');
  $tempday = date('j');
  $tempyear = date('Y');
  $currentdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  
  // AU2009
  $tempmonth = 8;
  $tempday = 28;
  $tempyear = 2009;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 12;
  $tempday = 10;
  $tempyear = 2009;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "AU2009";
  }
  
  // WI2010
  $tempmonth = 12;
  $tempday = 11;
  $tempyear = 2009;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 3;
  $tempday = 18;
  $tempyear = 2010;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "WI2010";
  }
  
  // SP2010
  $tempmonth = 3;
  $tempday = 19;
  $tempyear = 2010;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 6;
  $tempday = 10;
  $tempyear = 2010;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "SP2010";
  }
  
  // SU2010
  $tempmonth = 6;
  $tempday = 11;
  $tempyear = 2010;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 8;
  $tempday = 27;
  $tempyear = 2010;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "SU2010";
  }
  
  // AU2010
  $tempmonth = 8;
  $tempday = 28;
  $tempyear = 2010;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 12;
  $tempday = 9;
  $tempyear = 2010;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "AU2010";
  }
  
  // WI2011
  $tempmonth = 12;
  $tempday = 10;
  $tempyear = 2010;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 3;
  $tempday = 17;
  $tempyear = 2011;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "WI2011";
  }
  
  // SP2011
  $tempmonth = 3;
  $tempday = 18;
  $tempyear = 2011;  
  $startdate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  $tempmonth = 6;
  $tempday = 9;
  $tempyear = 2011;  
  $enddate = mktime(0, 0, 0, $tempmonth, $tempday, $tempyear);
  if ($currentdate > $startdate && $currentdate < $enddate) {
    $quarter = "SP2011";
  }
  
  // Registrar information ends here. This file will need to be updated.
  
  // Return the quarter and date
  return $quarter;
}