#define MAX_TOK_SIZE 25

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
