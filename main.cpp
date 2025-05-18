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

bool set_next_cmd(char **argv, char ***next_cmd) {
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

void redirect_io(int dup_fds[2]) {
    dup2(dup_fds[IN], 0);
    close(dup_fds[IN]);
    dup2(dup_fds[OUT], 1);
    close(dup_fds[OUT]);
}

void exec_cd(char **argv) {
    if (chdir(argv[1]) == -1) {
        perror("cd");
    }
}

void exec_cmd(int fd[2], char **argv, char **envp) {
    int dup_fds[2];
    dup_fds[OUT] = dup(fd[OUT]);
    dup_fds[IN] = dup(fd[IN]);
    if (argv[0]) {
        if (!strncmp(argv[0], "cd", 3))
            exec_cd(argv);
    }
    else {
        pid_t pid = fork();
        if (pid == 0) {
            redirect_io(dup_fds);
            execve(*argv, argv, envp);
        } else {
            wait(NULL); // Wait for the child to complete
        }
    }
    close(dup_fds[IN]); // Close the read end in the parent
    close(dup_fds[OUT]); // Close the write end in the parent
}

void pipe_exec(int *in_fd, char **argv, char **envp) {
    int fd[2];

    pipe(fd);
    dup2(fd[IN], *in_fd);
    close(*in_fd);
    exec_cmd(fd, argv, envp);
    close(fd[OUT]);
    *in_fd = fd[IN];
}

int main(int argc, char** argv, char **envp) {
    (void)argc;
    char **next_cmd;
    int is_pipe = FALSE;
    int fds[2];

    argv = &argv[1];
    fds[IN] = dup(0);
    fds[OUT] = dup(1);
    while (argv && *argv) {
        is_pipe = set_next_cmd(argv, &next_cmd);
        if (is_pipe) {
            pipe_exec(&fds[IN], argv, envp);
        } else {
            exec_cmd(fds, argv, envp);
        }
        argv = next_cmd;
    }
    return (0);
}
