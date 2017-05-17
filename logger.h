/*
 * logger.h
 *
 *  Created on: 13 Mar 2017
 *      Author: bj
 */

#ifndef LOGGER_H_
#define LOGGER_H_

extern void file_remove_log(char CurrentUser, char FileName);
extern void file_add_log(char CurrentUser, char FileName);
extern void file_print_log(char CurrentUser, char FileName);
extern void share_list_log();
extern void settings_create_log();


#endif /* LOGGER_H_ */
