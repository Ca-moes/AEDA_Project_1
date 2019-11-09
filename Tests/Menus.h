//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_MENUS_H
#define PROJECT_1_MENUS_H
#include "Delegation.h"
#include <iostream>

/**
 * Check if the input option is valid in a Menu
 *
 * @param test the number to check
 * @param lowerlimit the minimum number(option) accepted by the menu
 * @param upperlimit the maximum number(option) accpeted by the menu
 * @returns 0 if the option exists in the menu and 1 otherwise
 */
int checkinputchoice(string& test, int lowerlimit, int upperlimit);

/**
 * Display main menu with option to manage a delegation in a friendly way, connecting to submenus
 *
 * @param delegation a delegation
 */
void mainMenu(Delegation &delegation);

/**
 * Display participants menu that redirects the user to submenus to manage athletes, teams, staff members and also to show all participants
 *
 * @param delegation a delegation
 */
void participantsMenu(Delegation & delegation);

/**
 * Display sports menu that redirects the user to submenus to manage competitions of a specific sport
 *
 * @param delegation a delegation
 */
void sportsMenu(Delegation & delegation);

/**
 * Display results menu that to show medals information
 *
 * @param delegation a delegation
 */
void resultsMenu(Delegation & delegation);

/**
 * Display staff's menu that allows the use to manage staff's members - add, remove, change and check information
 *
 * @param delegation a delegation
 */
void staffMenu(Delegation & delegation);

/**
 * Display athletes menu that allows the user to add, remove, change athletes and to check athletes information
 *
 * @param delegation a delegation
 */
void athletesMenu(Delegation & delegation);

/**
 * Display teams menu that allows the user to add, remove, change teams and to check athletes information
 *
 * @param delegation a delegation
 */
void teamsMenu(Delegation & delegation);

/**
 * Display options to end participation in a sport or to see it's competitions/trials
 *
 * @param delegation a delegation
 * @param sport the sport to check for competitions
 */
void sportOptionsMenu(Delegation & delegation, const string & sport);

/**
 * Display competitions of a sport in a friendly way
 *
 * @param delegation a delegation
 * @param sport the sport to check for competitions
 */
void competitionsMenu(Delegation & delegation, const string & sport);
#endif //PROJECT_1_MENUS_H
