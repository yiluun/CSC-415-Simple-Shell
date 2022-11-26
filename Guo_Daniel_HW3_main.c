/**************************************************************
 * Class:  CSC-415-01 Summer 2022
 * Name: Daniel Guo
 * Student ID: 913290045
 * GitHub ID: yiluun
 * Project: Assignment 3 – Simple Shell
 *
 * File: Guo_Daniel_HW3_main.c
 *
 * Description: This assignment is to build our own shell on
 * top of Linux's using fork and execvp.
 *
 **************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 130

int main(int argc, char *argv[])
{

    char *buffer;
    // array to hold N + 1 pointers
    char *tokens[BUFFER_SIZE / 2 + 1];
    buffer = malloc(BUFFER_SIZE);

    while (1)
    {

        printf("prompt$ ");

        if (fgets(buffer, BUFFER_SIZE, stdin))
        {

            // parse string into tokens array
            tokens[0] = strtok(buffer, " \t\n");

            // check if nothing is input by the user, and prompt them again
            if (!tokens[0])
            {
                continue;
            }

            // strstr function to check if "exit" is the first command typed by user, so we can safely exit
            // will terminate to parent shell
            if (strstr(tokens[0], "exit"))
            {
                return 0;
            }

            int i = 0;
            // process tokens
            while (tokens[i])
            {
                i++;
                tokens[i] = strtok(NULL, " \t\n");
            }
        }

        else
        {
            return 0;
        }

        int status;
        pid_t ID = fork();

        // if fork fails
        if (ID == -1)
        {
            printf("Fork Error: -1");
        }
        // if child process is successfully created
        else if (ID == 0)
        {
            // if successful, will replace current process
            // execvp will automatically find executable file
            execvp(tokens[0], tokens);
        }
        else
        {
            wait(&status);
            // WIFEXITED checks if child process has died normally
            if (WIFEXITED(status))
            {
                int result = WEXITSTATUS(status);
                printf("Child %d, exited with %d\n", getpid(), result);
            }
        }
    }

    free(buffer);

    return 0;
}
