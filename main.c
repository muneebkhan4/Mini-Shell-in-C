#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_PATHS 9
#define MAX_PATH_LEN 96
#define WHITESPACE " .,\t\n"

#ifndef NULL
#define NULL ...
#endif
#include"minishell.h"


int main()
{

    struct command_t command;       // stores command, argv and argc

    char *dir[20];    // stores directories

    while(1)
    {
        
        for(int i=0;i<20;i++)
        {
            dir[i] = malloc(30);    // allocating dynamic memory
        }
    
    
        print_prompt();             // print prompt

        command.argc = read_command(command.name, command.argv);    // reading command
        
        

        if(strcmp(command.name, "exit")==0)         // if command is exit
        {

           break;
        }
    
    
    
        command.argv[command.argc]= NULL;         // making null terminated

        parsePath(dir);                            // parsing path

        char* path = lookupPath(command.argv,dir);    // getting exact path
    
        
        int pid= fork();                        // making child process
        
        if(pid==0)
        {
            execv(path, command.argv);          // running execv in child process
            printf("\nError\n");                // print error in case of failure
        }   
        else
        {
            wait(NULL);
            for(int i=0;i<20;i++)
            {
                free(dir[i]);                   // free the dynamic memory
            }
            for(int i=0;i<command.argc;i++)
            {
                free(command.argv[i]);          // free dynamic memory of argv which is in command struct
            }
            printf("\nend\n");
        }
       
    }        

    
    for(int i=0;i<20;i++)
    {
        free(dir[i]);                   // free the dynamic memory
    }
    for(int i=0;i<command.argc;i++)
    {
        free(command.argv[i]);          // free dynamic memory of argv which is in command struct
    }
    
    
    return 0;
}
