#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env) {
    pid_t pid;
    int status;

    // Fork a child process
    pid = fork();
	int	i = 0;
	while (env[i])
	{
		i++;
	}
	char **my_env = malloc(i + 2);
	i = 0;
	while (env[i])
	{
		my_env[i] = env[i];
		i++;
	}
	my_env[i++] = "PS1=minishell> ";
	my_env[i] = NULL;
    if (pid == -1) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid == 0) {
        char *args[] = { "bash", "--rcfile", "/dev/null", NULL };
        execve("/bin/bash", args, my_env);
        perror("execve");
        return 1;
    } else {
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
    }

    return 0;
}
