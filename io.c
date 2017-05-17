/*
 * io.c
 *
 *  Created on: 13 Mar 2017
 *      Author: bj
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <fcntl.h>
#include "logger.h"




//Function to create main menu screen for user input.
int Option_Select(int selection)
{
	char select[3];
	printf("Please select from the following menu:\n1.Add File\n2.Delete File\n3.View File\n4.Add Friend\n5.Exit\n");
	fgets(select,3,stdin);

	selection = atoi(select);

	return selection;
}


//Function to add a new file to the file list
void write_new_file(char NewFile[40],char CurrentUser[30])
{
	FILE *fp = fopen("FilesList.txt","a+");
	fprintf(fp,"%s",NewFile);
	fclose(fp);
	file_add_log(*CurrentUser, *NewFile);
}

//Function to prompt user for the details of the new file.
void prompt_new_file(char CurrentUser[30])
{
	char filename[30];
	char filepath[100];
	char fileperms[300];
	char strNewFile[430];

	printf("Enter filename:\n");
	fgets(filename,sizeof(filename),stdin);
	sscanf(filename,"%s%*[\n]",filename);
	printf("Enter filepath:\n");
	fgets(filepath,sizeof(filepath),stdin);
	sscanf(filepath,"%s%*[^\n]",filepath);
	printf("Enter up to 10 user names(Including your own username, seperated by a ,):\n");
	fgets(fileperms,sizeof(fileperms),stdin);
	sscanf(fileperms,fileperms);
	strcpy(strNewFile,"FN:");
	strcat(strNewFile,filename);
	strcat(strNewFile,";FP-");
	strcat(strNewFile,filepath);
	strcat(strNewFile,";Perms#");
	strcat(strNewFile,fileperms);


	write_new_file(strNewFile,CurrentUser);
}

//Function to add a friend to the friends list
char prompt_new_friend()
{
	char *friend_details, *username, *host_ip, *port;
	int portno;


	friend_details = malloc(sizeof(*friend_details));
	username = malloc(sizeof(*username));
	host_ip = malloc(sizeof(*host_ip));
	port = malloc(sizeof(*port));

	portno = 0;

	printf("Enter the username of the friend you wish to add:\n");
	fgets(username,sizeof(username),stdin);
	sscanf(username,"%s%*[\n]",username);
	printf("Enter the hostname/IP address of your friend:\n");
	fgets(host_ip,sizeof(host_ip),stdin);
	sscanf(host_ip,"%s%*[\n]",host_ip);
	printf("Enter your friends port number:\n");
	fgets(port,sizeof(port),stdin);
	sprintf(port,"%d",portno);
	strcpy(friend_details, "Username:");
	strcat(friend_details,username);
	strcat(friend_details,"H/IP-");
	strcat(friend_details,host_ip);
	strcat(friend_details,"Port~");
	strcat(friend_details,port);


	printf("%s",friend_details);
	return *friend_details;
}

//Function to check the permissions of the file being accessed.
int check_file_permissions(char FileName[30],char CurrentUser[30],int FilePermit)
{
	int i = 0;
	char buffer[300];
	char label[100];
	char value[100];
	char strOutPut[100];
	FILE *fp = fopen("FilesList.txt","r+");


	while (i< sizeof(fp) && fgets(buffer,120,fp) != NULL)
	{

		sscanf(buffer,"%[^:%s]",label);

		if (!strcmp(label,"FN"))
		{
			sscanf(buffer,"%*[^:]:%[^;];",value);

			value [strcspn(value, "\r\n")] = '\0';
			FileName [strcspn(FileName, "\r\n")] = '\0';

			if(strcmp(FileName,value)==0)
			{
				sscanf(buffer,"%*[^#]#%[^\n]",strOutPut);
				if(!strcmp(CurrentUser,strOutPut))
				{
					FilePermit = 1;
					printf("Access permitted\n");
					return FilePermit;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}

		}
		else if(EOF)
		{
			printf("File does not exist in list");
			return FilePermit;
		}
		else
		{
			continue;
		}
		fclose(fp);
	}
	return FilePermit;
}

//Function to view a file if permitted.
void view_file(char CurrentUser[30])
{
	char FileName[30];
	char strOutPut[300];
	int FilePermit = 0;



	printf("Current user is:%s\n",CurrentUser);
	printf("Enter the name of the file you wish to view:\n");
	fgets(FileName,30,stdin);
	sscanf(FileName,FileName);
	printf("Checking Permissions for %s...\n",CurrentUser);
	FilePermit = check_file_permissions(FileName,CurrentUser,FilePermit);

	if(FilePermit==1)
	{
		printf("File contents below:\n\n");
		FILE *fp = fopen(FileName,"r+");
		fgets(strOutPut,300,fp);
		printf("%s",strOutPut);
		fclose(fp);
		printf("\n\n");
		file_print_log(*CurrentUser,*FileName);
	}
	else
	{
		printf("You are not permitted to view %s",FileName);
	}
}

//Function to delete a file if permitted.
void delete_file(char CurrentUser[30])
{
	int FilePermit = 0;
	int i = 0;
	char buffer[300];
	char FileName[30];
	char * FullPath = malloc(sizeof(char)*50);
	char FilePath[100];
	char label[10];
	char value[100];
	char * LineOut = malloc(sizeof(char)*50);
	char OldName[30] = "temp.txt";
	char NewName[30] = "FilesList.txt";

	printf("Enter the name of the file you wish to delete:\n");
	fgets(FileName,30,stdin);
	sscanf(FileName,FileName);
	printf("Checking Permissions for %s...\n",CurrentUser);
	FilePermit = check_file_permissions(FileName,CurrentUser,FilePermit);
	FILE *tf = fopen("temp.txt","a+");
	if(FilePermit == 1)
	{
		FILE *fp = fopen("FilesList.txt","r+");


		while(i<sizeof(buffer) && fgets(buffer,100,fp) != NULL)
		{
			sscanf(buffer,"%[^:%s]",label);

			if (!strcmp(label,"FN"))
			{
				sscanf(buffer,"%*[^:]:%[^;];",value);

				value [strcspn(value, "\r\n")] = '\0';
				FileName [strcspn(FileName, "\r\n")] = '\0';

				if(strcmp(FileName,value)==0)
				{
					sscanf(buffer,"%*[^:]:%*[^-]-%s",FilePath);
					printf("%s",FilePath);
					strcat(FullPath,FileName);
					file_remove_log(*CurrentUser,*FileName);
					continue;
				}
				else
				{
					printf("%s",buffer);
					fprintf(tf,buffer);
					strcat(LineOut,buffer);
				}
			}
			else
			{
				continue;
			}
		}

		printf("Test");
		printf("%s",LineOut);

		if(LineOut != NULL)
		{
			printf("Removing File");
			fclose(tf);
			fclose(fp);
			remove("FilesList.txt");
			rename(OldName,NewName);
			remove("temp.txt");
			printf("File Removed");
		}
	}
	else
	{
		printf("You are not permitted to delete this file\n");
	}
}
