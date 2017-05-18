/*
 * logger.c
 *
 *  Created on: 13 Mar 2017
 *      Author: bj
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



void file_remove_log(char CurrentUser[30],char FileName[30])
{
	FILE *fp = fopen(("FileShare.log"), "ab+");
	fprintf(fp, "File %s was removed by %s", FileName, CurrentUser);
	fclose(fp);
}

void file_add_log(char CurrentUser[30], char FileName[40])
{
	FILE *fp = fopen(("FileShare.log"), "ab+");
	fprintf(fp, "File %s was added by %s", FileName, CurrentUser);
	fclose(fp);
}

void file_print_log(char CurrentUser[30],char FileName[30])
{
	FILE *fp = fopen(("FileShare.log"), "ab+");
	fprintf(fp, "File %s was printed/viewed by %s", FileName, CurrentUser);
	fclose(fp);
}

void share_list_log()
{
	FILE *fp = fopen(("FileShare.log"), "ab+");
	fprintf(fp, "Sharelist File Created");
	fclose(fp);
}

void settings_create_log()
{
	FILE *fp = fopen(("FileShare.log"), "ab+");
	fprintf(fp, "Settings.conf created/edited");
	fclose(fp);
}

