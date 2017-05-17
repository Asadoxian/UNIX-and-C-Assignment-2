/*
 * io.h
 *
 *  Created on: 13 Mar 2017
 *      Author: bj
 */

#ifndef IO_H_
#define IO_H_

extern int Option_Select(int selection);
extern int read_user_name(char value,char buffer);
extern int read_ip_address(char value,char buffer);
extern int read_port_no(int value,char buffer);
extern void prompt_new_file();
extern void write_new_file(char filename, char filepath,char permissions);
extern void file_exists(char filename);
extern void prompt_new_friend();
extern void delete_file(char CurrentUser);
extern void view_file(char CurrentUser);

#endif /* IO_H_ */
