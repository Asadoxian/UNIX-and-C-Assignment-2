/*
 * files.c
 *
 *  Created on: 13 Mar 2017
 *      Author: bj
 */
//Include all required libraries and external headers
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <fcntl.h>
#include "io.h"
#include "logger.h"
#include <sys/socket.h>
#include <arpa/inet.h>

//Define required variables

typedef struct {char user_name[30];char ip_address[32];int port_no;} user_settings;

typedef struct {
	char filename[30];
	char filepath[30];
	char permissions[30];
} file_structs;

typedef struct {char user_name[30];char host_ip[40];int port_no;} friends_list;

//Function to check for files existence or create if it doesn't exist (wouldn't work in IO.C)
void File_Exists(char filename[])
{
	if( access( filename, F_OK ) != -1 ) {
	    // file exists
	} else {
		perror("File does not exist creating");
		FILE *fp = fopen(filename, "ab+");
		fclose(fp);
	}
}


int main(int argc, char* argv[])
{
	//Initialize all the variables
	char *Name, *IP;
	Name = malloc(sizeof(*Name));
	IP = malloc(sizeof(*IP));
	strcpy(Name,"Share User");
	strcpy(IP,"192.168.3.12");
	int PortNo = 29045;
	int *selection;

	selection = malloc(sizeof(*selection));
	selection = 0;

	char *New_IP, *New_Name, *New_PortStr;

	New_IP = malloc(sizeof(*New_IP));
	New_Name = malloc(sizeof(New_Name));
	New_PortStr = malloc(sizeof(*New_PortStr));
	int New_PortNo = 0;

	char *label, *NameLab, *IPLab, *PortNoLab;
	label = malloc(sizeof(*label));
	NameLab = malloc(sizeof(*NameLab));
	IPLab = malloc(sizeof(*IPLab));
	PortNoLab = malloc(sizeof(*PortNoLab));
	strcpy(NameLab,"Name:");
	strcpy(IPLab,"IP:");
	strcpy(PortNoLab, "PortNo:");



	//Check for file list file and log file exists

	File_Exists("FilesList.txt");
	File_Exists("FriendsList.txt");
	File_Exists("FileShare.log");
	share_list_log();

	//Create default settings and populate it. Copy the default settings to current settings and create a pointer to that.

	user_settings default_settings = {0};
	strcpy(default_settings.user_name,Name);
	strcpy(default_settings.ip_address,IP);
	default_settings.port_no = PortNo;
	user_settings current_settings;
	current_settings = default_settings;
	user_settings *s;
	s = &current_settings;

	//Code to check settings.conf exists and if not create it and copy the default settings to settings.conf
	//If settings.conf exists copy settings to current_user struct.

	int settings = open("settings.conf", O_RDONLY | O_WRONLY);
	if (settings < 0)
	{
		FILE *fp = fopen("settings.conf", "a+");
		fclose(fp);
		FILE *wp = fopen("settings.conf", "a+");
		fprintf(wp,"%s%s\n%s%s\n%s%i",NameLab,s->user_name,IPLab,s->ip_address,PortNoLab,PortNo);
		fclose(wp);
		settings_create_log();
	}
	else
	{
		FILE *fp = fopen("settings.conf","r+");
		char buffer[sizeof s];
		int i = 0;

		while(i<sizeof(buffer) && fgets(buffer,30,fp) != NULL)
				{
				    if(buffer[0] != '#')
				    {
				    	sscanf(buffer,"%[^:%c]",label);
				    	if(!strcmp(label,"IP"))
				    	{
				    		sscanf(buffer,"%*[^:]%*c%[^\n]",New_IP);
				       	}
				    	else if(!strcmp(label,"Name"))
				    	{
				    		sscanf(buffer,"%*[^:]%*c%[^\n]",New_Name);
				    	}
				    	else if(!strcmp(label,"PortNo"))
						{
							sscanf(buffer,"%*[^:]%*c%[^\n]",New_PortStr);
							New_PortNo = atoi(New_PortStr);
						}
				    	else
				    	{
				    		printf("No data found");
				    	}
				    }
				}
	}
	if(strcmp(New_IP,s->ip_address))
		strcpy(s->ip_address,New_IP);
	if(strcmp(New_Name,s->user_name))
		strcpy(s->user_name,New_Name);
	if(New_PortNo != s->port_no)
		s->port_no = New_PortNo;


	create_listen_socket();
	//Run main IO loop to prompt for input from the user for options. Or exit the application.

	selection = Option_Select(selection);

	switch(*selection)
	{
	case 1:
		prompt_new_file(s->user_name);
		break;

	case 2:
		delete_file(*s->user_name);
		break;

	case 3:
		view_file(*New_Name);
		break;

	case 4:
		prompt_new_friend();
		break;

	case 5:
		exit(1);

	default:
		printf("\nError enter 1 - 5 for your selection \n");
		break;
	}

}



