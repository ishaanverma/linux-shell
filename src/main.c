#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MAX_HIS_SIZE 100

int status = 1;
char *history[MAX_HIS_SIZE];
int last = 0;


void add_history(char *line)    {

    history[last % MAX_HIS_SIZE] = line;
    last++;
    
}

void get_history()  {
    int i;

    for(i=0; i < last; i++) {
        printf("%s\n", *(history + i));
    }
}

char *read_line()   {
    static char *line_read = (char *) NULL;
    char c;
    int position = 0;

    if (line_read)  {
        free(line_read);
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

int main(int argc, char *argv[])    {
    char *line, *token;

    do  {

        line = read_line();
        //token = tokenize(line);
        //printf("%s\n", line);
        get_history();
    } while(status);


    return 0;
}
