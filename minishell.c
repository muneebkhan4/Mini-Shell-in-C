#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

#include"minishell.h"
//---------------------------------------------------  READ COMMAND  ------------------------------------------------//

int read_command(char cmd[], char* para[])
{   
    char line[1024];                // to get the input
    int count = 0, i = 0, j = 0, k=0;    // control the function
    int c;
    
    fgets(line, 1024, stdin);          // taking the line as input
    char* temp = malloc(30);
    for( i=0;line[i]!='\0';i++)
    {
        if(line[i]==' ' | line[i+1]== '\0')
        {
            temp[j] = '\0';
            para[k]= malloc(30);
            for(int a=0;temp[a]!='\0';a++)      // separateing the word on basis of space
            {
                para[k][a] = temp[a];
            }
            k++;
            j=0;
            free(temp);
            temp= malloc(30);
            if(line[i+1]=='\0')
            para[k]=NULL;
        }
        else
        {
            temp[j] = line[i];
            j++;
        }
        

    }
    
    strcpy(cmd,para[0]);            // taking first word as command
    return k;                       // it return total numbers of words in the line...
}

//---------------------------------------------------  PRINT PROMPT   ------------------------------------------------//

void print_prompt()					// print prompt on screen
{
     const char*CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);	// clear screen
    
    char buff[100];
   
    printf("muneeb@19L_2267-VirtualBox:~");
    
    getcwd(buff,50);			// current directory
    
    printf("%s", buff);
    
    printf("$ ");
}

//---------------------------------------------------  PARSE PATH   ------------------------------------------------//
 
void parsePath(char *dirs[]) 
{
    /* This function reads the PATH variable for this
    * environment, then builds an array, dirs[], of the
    * directories in PATH
    */

    char *pathEnvVar;
    char *thePath;
    
    pathEnvVar = (char *) getenv("PATH");           // getting environment variables
    thePath = (char *) malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

    printf("\nDir: %s\n", pathEnvVar);



    /* Loop to parse thePath. Look for a ":"
    * delimiter between each path name.
    */
    
    int k=0, j=0;
    char temp[30];
    int count=0;
    for(int i=0;i<strlen(thePath);i++)         // separating on basis of : and storing in dirs
    {
        temp[k] = thePath[i];
        k++;
        if(thePath[i]==':')
        {
           temp[k-1]='\0';
           dirs[j] = malloc(k);
           strcpy(dirs[j] , temp);
           j++;
           k=0;
           count++;
        }
        
        if(i==strlen(thePath)-1)
        {
            temp[k]='\0';
           dirs[j] = malloc(k);
           strcpy(dirs[j] , temp);
           count++;
        }
    }
    
}

//---------------------------------------------------  LOOK UP PATH   ------------------------------------------------//

char* lookupPath(char **argv, char **dir) 
{
    /* This function searches the directories identified by the dir
    * argument to see if argv[0] (the file name) appears there.
    * Allocate a new string, place the full path name in it, then
    * return the string.
    */
    
    char *result;
    char pName[MAX_PATH_LEN];

    // Check to see if file name is already an absolute path
    if (*argv[0] == '/' | *argv[0] == '.')      // check for absolute path or external command
    {
        
        result= malloc(strlen(argv[0])+1);
        strcpy(result, argv[0]);  
        return result;    
    }

    // Look in PATH directories.
    // Use access() to see if the file is in a dir.

    for (int i = 0; i < MAX_PATHS; i++) 
    {
        result= malloc(strlen(argv[0])+strlen(dir[i])+1);
        strcpy(result, dir[i]);
        strcat(result, "/");
        strcat(result, argv[0]);
        printf("\n%s\n", result);
        int fd = access(result, X_OK);      // checking for access of the command in each directory
        if(fd==0)
        {
            return result;
        }
        free(result);
    }

    // File name not found in any path variable
    fprintf(stderr, "%s: command not found\n", argv[0]);        // if command is not found
    return NULL;
}

