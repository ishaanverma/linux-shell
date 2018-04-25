#include<unistd.h>
#define MAX_DIR_SIZE 1024

char cwd[MAX_DIR_SIZE];
char *commands_list[] = {
    "cd",
    "pwd",
    "history",
    "exit",
    "PS1"
};

int exec_pwd()   {
    if (getcwd(cwd, sizeof(cwd)) != NULL)   {
        return 1;
    }
    else
        return 0;
}

int exec_cd(char **args)  {
    chdir(args[1]);
    exec_pwd(NULL);
    return 1;
}

int exec_exit() {
    exit(0);
}

char *exec_prompt(char **args)    {
    static char prompt[3] = ">>";

    if (args[2] != NULL)
        prompt[0] = *args[2];

    return (prompt);
}
