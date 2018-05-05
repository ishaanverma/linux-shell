#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "built_in_commands.h"
#include "token.h"

#define BUFFER_SIZE 1024
#define MAX_HIS_SIZE 100

int status = 1;
char *history[MAX_HIS_SIZE];
int front = -1, last = 0;

int execprogram(char **argu);
int exec_most_recent(int n);
int exec_n_cmd(char **argu);

void add_history(char *line)    {
    if (front == -1)
        front += 1;

    if (last >= MAX_HIS_SIZE)   {
        free(history[front]);
        front = (front + 1) % MAX_HIS_SIZE;
    }

    history[last % MAX_HIS_SIZE] = line;
    last++;
}

void exec_history()  {
    int i;
    printf("----------HISTORY-----------\n");
    for(i=front; i < MAX_HIS_SIZE; i++) {
        if (*(history + i)) {
            printf("%s\n", *(history + i));
        }
        else    {
            break;
        }
    }

    for(i=0; i < front; i++)    {
        printf("%s\n", *(history + i));
    }

    printf("----------------------------\n");
}

char *read_line()   {
    static char *line_read = (char *) NULL;
    char c;
    int position = 0;

    if (line_read)  {
        line_read = (char *) NULL;
    }

    line_read = malloc(sizeof(char) * BUFFER_SIZE);

    while (1)  {
        c = getchar();

        if (c != EOF && c != '\n')  {
            line_read[position] = c;
            position++;
        }
        else    {
            line_read[position] = '\0';
            break;
        }
    }

    if (line_read && *line_read)
        add_history(line_read);

    return (line_read);

}

int execprogram(char **argu)    {
    int i;
    int len = sizeof(commands_list) / sizeof(commands_list[0]);
    pid_t pid;

    if  (argu == NULL)
        return 0;

    for(i=0; i < len; i++)  {
        if (strcmp(argu[0], commands_list[i]) == 0)    {
            switch(i)   {
                case 0: exec_cd(argu);
                        break;
                case 1: exec_pwd();
                        break;
                case 2: exec_history();
                        break;
                case 3: exec_exit();
                        break;
                case 4: exec_most_recent(2);
                        break;
                case 5: exec_n_cmd(argu);
                        break;
                default: printf("Not command function found\n");
            }

            return 1;
        }
    }

    pid = fork();
    //child
    if (pid == 0)   {
        int estat;
        estat = execvp(argu[0], argu);

        if (estat == -1)    {
            printf("Unkown Command\n");
        }
        exit(0);
    }
    //parent
    else    {
        wait(NULL);
        return 1;
    }
}

int exec_most_recent(int n)   {
    if (!n || n <= 1)  {
        n = 2;
    }

    char **arg;
    int index;
    index = last-(1*n)-1;

    if (index < 0)
        index = 0;

    arg = tokenize(history[index], ' ');
    execprogram(arg);
}

int exec_n_cmd(char **argu)    {
    if (argu[1] == NULL)
        return 1;

    exec_most_recent(atoi(argu[1]));
}

int welcome_screen(char *name)   {
    FILE *fptr = NULL;
    char read_string[BUFFER_SIZE];

    if ((fptr = fopen(name, "r")) == NULL)  {
        fprintf(stderr, "error opening %s\n", name);
        return 1;
    }

    while(fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);

    printf("\n \n");

}

int main(int argc, char *argv[])    {
    char *line, *token, **argu;
    char *filename = "image.txt";
    welcome_screen(filename);

    do  {
        exec_pwd();
        printf("%s >> ", cwd);
        line = read_line();
        argu = tokenize(line, ' ');

        if (execprogram(argu))
            continue;

    } while(status);


    return 0;
}
