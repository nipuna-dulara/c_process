#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 9
#define MAX_LINE_LEN 128

void execute_command(char *args[])
{
    if (execvp(args[0], args) == -1)
    {

        exit(2);
    }
}

int main(int argc, char *argv[])
{
    char *args[MAX_ARGS + 1];
    char input_line[MAX_LINE_LEN];
    int placeholder_count = 0;
    int i;
    int pid;

    for (i = 0; i < argc - 1; i++)
    {
        if (strcmp(argv[i + 1], "%") == 0)
        {
            placeholder_count++;
        }
        args[i] = strdup(argv[i + 1]);
    }
    args[i] = NULL;

    if (placeholder_count == 0)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(4);
        }
        else if (pid == 0)
        {
            execute_command(args);
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
        for (i = 0; i < argc - 1; i++)
        {
            free(args[i]);
        }
        return 0;
    }

    while (fgets(input_line, sizeof(input_line), stdin) != NULL)
    {
        input_line[strcspn(input_line, "\n")] = '\0';
        char *tokens[MAX_ARGS];
        int token_count = 0;
        char *token = strtok(input_line, " ");
        while (token != NULL && token_count < MAX_ARGS)
        {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }
        int arg_index = 0;
        int token_index = 0;
        for (i = 0; i < argc - 1; i++)
        {
            if (strcmp(args[arg_index], "%") == 0)
            {
                if (token_index < token_count)
                {
                    args[arg_index] = tokens[token_index++];
                }
                else
                {
                    args[arg_index] = NULL;
                }
            }
            arg_index++;
        }
        args[arg_index] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(3);
        }
        else if (pid == 0)
        {
            execute_command(args);
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }

        for (i = 0; i < argc - 1; i++)
        {
            if (strcmp(argv[i + 1], "%") == 0)
            {
                args[i] = strdup(argv[i + 1]);
            }
        }
        args[argc - 1] = NULL;
    }

    for (i = 0; i < argc - 1; i++)
    {
        free(args[i]);
    }

    return 0;
}
