#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_HIS_SIZE 100
#define MAX_TOK_SIZE 25

int status = 1;
char *history[MAX_HIS_SIZE];
int front = -1, last = 0;


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

void get_history()  {
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

char **tokenize(char *line, char delimiter)  {

    static char *args[MAX_TOK_SIZE];
    int length = strlen(line);
    int i = 0, tokens = 0;
    char *new_line = (char *) NULL;


    new_line = realloc(line, (sizeof(char) * length));

    if (!(*new_line))
        return NULL;

    args[tokens] = new_line;
    tokens++;
    for (i=0; i < length; i++)  {
        if (new_line[i] == delimiter)   {
            new_line[i] = '\0';

            if (new_line[i+1] != delimiter)    {
                args[tokens] = new_line + (i * sizeof(char)) + 1;
                tokens++;
            }
        }
    }

    return args;
}

int execprogram(char **argu)    {
    int pid;
    pid = fork();

    //child
    if (pid == 0)   {
        int r;
        r = execvp(argu[0], argu);

        if (r == -1)    {
            printf("Unkown Command\n");
        }
        exit(0);
    }
    //parent
    else    {
        wait(&pid);
        return 1;
    }
}

int main(int argc, char *argv[])    {
    char *line, *token, **argu;

    do  {

        line = read_line();
        argu = tokenize(line, ' ');
        execprogram(argu);
        //printf("%s\n", line);
        //get_history();
    } while(status);


    return 0;
}
