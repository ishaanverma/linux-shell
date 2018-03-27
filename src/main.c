#include <stdio.h>
#include <stdlib.h>


int status = 1;
int BUFFER_SIZE = 1024;

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
        //add_history(line_read);

    return (line_read);

}
int main(int argc, char *argv[])    {
    char *line;

    do  {
        // get_string() fucntion will call the GNU readline function
        line = read_line();
        printf("%s", line);
    }while(status);


    return 0;
}
