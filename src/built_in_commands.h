#include<unistd.h>
#define MAX_DIR_SIZE 1024

char cwd[MAX_DIR_SIZE];
char *commands_list[] = {
    "cd",
    "pwd",
    "history",
    "exit",
    "!!",
    "!"
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
    exec_pwd();
    return 1;
}

int exec_exit() {
    exit(0);
}
