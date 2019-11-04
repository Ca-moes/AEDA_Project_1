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
 * Display main menu with option to manage a delegation in a friendly way
 *
 * @param delegation a delegation
 */
void mainMenu(Delegation &delegation);


#endif //PROJECT_1_MENUS_H
