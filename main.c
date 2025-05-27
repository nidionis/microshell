#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int update_next_cmd(char ***argv, char ***next_cmd) {
	int is_piped = 0;
	*next_cmd = *argv;
	while (*argv && **argv) {
		if (strcmp(**argv, "|") || strcmp(**argv, ";")) {
			if (strcmp(**argv, "|"))
				is_piped = 1;
			**argv = NULL;
			*argv = *argv + 1;
			break;
		}
		(*argv)++;
	}
	return is_piped;
}

int tmp;

int p(char *s)
{
	while (*s)
		write(2, s++, 1);
	return 1;
}

int builtin_cd(char **argv, int i)
{
	if (i != 2)
		return p("error: cd: bad arguments\n");
	if (chdir(argv[1]))
		return p("error: cd: cannot change directory to ") & p(argv[1]) & p("\n");
	return 0;
}

int ft_exec(char **argv, char **ep, int i)
{
	int fds_pipe[2], r;
	int is_pipe = (argv[i] && !strcmp(argv[i], "|"));

	if (is_pipe)
	   pipe(fds_pipe);

	int pid = fork();
	if (!pid)
	{
		argv[i] = 0;
		dup2(tmp, 0);
		close(tmp);
		if (is_pipe) {
			dup2(fds_pipe[1], 1);
			close(fds_pipe[0]);
			close(fds_pipe[1]);
		}
		execve(*argv, argv, ep);
	}
	if (is_pipe) {
		dup2(fds_pipe[0], tmp);
		close(fds_pipe[0]);
		close(fds_pipe[1]);
	} else 
		dup2(0, tmp);

	waitpid(pid, &r, 0);
	return WIFEXITED(r) && WEXITSTATUS(r);
}

int main(int ac, char **argv, char **ep)
{
	(void)ac;
	int i = 0, r = 0;
	tmp = dup(0);
	while (argv[i] && argv[++i])
	{
		argv = argv + i;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (!strcmp(*argv, "cd"))
			r = builtin_cd(argv, i);
		else if (i)
			r = ft_exec(argv, ep, i);
	}
	dup2(0, tmp);
	return (0);
}
