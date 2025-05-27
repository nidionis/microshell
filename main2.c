#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define STDOUT 1

int set_next_cmd(char **argv, char ***next_cmd) {
    *next_cmd = argv;
    int is_pipe = 0;
    while (argv && *argv && **argv) {
        if (!strncmp(*argv, ";", 2) || !strncmp(*argv, "|", 2)) {
            *next_cmd = &argv[1];
            break ;
        }
        argv++;
    }
    if (argv && *argv && strncmp(*argv, "|", 2))
        is_pipe = 1;
    *argv = NULL;
    return (is_pipe);
}

void dup_fds(int fds[2], int fd_in) {
    dup2(fds[0], fd_in);
    close(fds[0]);
    dup2(fds[1], STDOUT);
    close(fds[1]);
}

void exec_cmd(char **argv, int *fd_in) {
    int fds[2];
    pid_t pid = fork();
    if (pid == 0) {
        dup_fds(fds, *fd_in);
        execve(argv[0], argv, NULL);
    }
}

void exec_in_pipe(char **argv, int *fd_in) {};

int main(int argc, char** argv) {
    char **next_cmd;
    int is_pipe;
    int fd_in = dup(0);
    argv = &argv[1];

    while (argv && *argv && **argv) {
        is_pipe = set_next_cmd(argv, &next_cmd);
        if (argv && *argv) {
            if (is_pipe) {
                exec_in_pipe(argv, &fd_in);
            } else {
                exec_cmd(argv, &fd_in);
            }
        }
        argv = next_cmd;
    }
    return (0);
}