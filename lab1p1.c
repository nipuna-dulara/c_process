#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARG_LEN 512
#define MAX_ARGS 8

void execute_command(char *command)
{

    char *argv[MAX_ARGS + 1] = {NULL};
    int argc = 0;
    char *token = strtok(command, " ");

    while (token != NULL && argc < MAX_ARGS)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    // for an empty command
    if (argc == 0)
    {
        argv[0] = "/bin/echo";
        argv[1] = "empty";
        argv[2] = "command";
        argc = 3;
    }

    argv[argc] = NULL;
    int pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "error = %d\n", errno);
        exit(2);
    }
    else if (pid == 0)
    {
        if (execve(argv[0], argv, NULL) == -1)
        {
            fprintf(stderr, "error = %d\n", errno);
            exit(3);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }

    char input[MAX_ARG_LEN];
    strncpy(input, argv[1], MAX_ARG_LEN);

    input[MAX_ARG_LEN - 1] = '\0';

    char *command = strtok(input, "+");

    while (command != NULL)
    {
        while (*command == ' ')
            command++;
        char *end = command + strlen(command) - 1;
        while (end > command && *end == ' ')
            end--;
        end[1] = '\0';
        execute_command(command);
        command = strtok(end + 3, "+");
    }

    return 0;
}
