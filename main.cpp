#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <wait.h>

#define IN 0
#define OUT 1
#define FALSE 0
#define TRUE 1

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

void exec_cmd(int in_fd, int out_fd, char **argv, char **envp) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (in_fd != 0) {
            dup2(in_fd, 0);
            close(in_fd);
        }
        if (out_fd != 1) {
            dup2(out_fd, 1);
            close(out_fd);
        }
        execve(*argv, argv, envp);
        perror("fatal : execve");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    } else {
        // Parent process
        if (in_fd != 0) {
            close(in_fd); // Close the read end in the parent
        }
        if (out_fd != 1) {
            close(out_fd); // Close the write end in the parent
        }
        wait(NULL); // Wait for the child to complete
    }
}

int main(int argc, char** argv, char **envp) {
    int fd[2];
    char **next_cmd;
    int is_pipe = FALSE;
    int in_fd = 0; // Start with standard input

    argv = &argv[1];
    while (argv) {
        is_pipe = set_next_cmd(argv, envp, &next_cmd);

        if (is_pipe) {
            if (pipe(fd) == -1) {
                perror("pipe");
                exit(1);
            }
            exec_cmd(in_fd, fd[OUT], argv, envp);
            close(fd[OUT]); // Parent closes write end
            if (in_fd != 0) {
                close(in_fd);
            }
            in_fd = fd[IN]; // Next command reads from pipe
        } else {
            exec_cmd(in_fd, 1, argv, envp);
            if (in_fd != 0) {
                close(in_fd);
            }
            in_fd = 0; // Reset to standard input
        }
        argv = next_cmd;
    }
    return (0);
}

