#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define IN 0
#define OUT 1

void print_tab(char **argv) {
    int i = 0;
    while (argv[i] != NULL) {
        printf("%s\n", argv[i]);
        i++;
    }
}

void print_cmd(char **argv) {
    printf("%s\n", "Command:");
    print_tab(argv);
}

bool set_next_cmd(char **argv, char **envp, char ***next_cmd) {
    int i = 0;
    int is_pipe = 0;
    *next_cmd = NULL;
    while (argv[i] != NULL) {
        if (!strncmp(argv[i], ";", 2) || !strncmp(argv[i], "|", 2)) {
            if (argv[i][0] == '|')
                is_pipe = 1;
            break ;
        }
        i++;
    }
    if (argv[i]) {
        argv[i] = NULL;
        *next_cmd = &argv[i + 1];
    }
    return (is_pipe);
}

int main(int argc, char** argv, char **envp) {
    int fd[2];
    char **next_cmd;
    dup2(fd[IN], 0);
    dup2(fd[OUT], 1);
    argv = &argv[1];
    while (argv) {
        printf("is pipe : %i\n", set_next_cmd(argv, envp, &next_cmd));
        print_cmd(argv);
        argv = next_cmd;
    }
    return (0);
}

