/* TODO: cambiar printf por write*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "../libft/libft.h"
#include <limits.h>

char *find_path(char *command, char *paths)
{
	char	*slash;
	char	*full_path;
	char	**splited;
	int		index = 0;
	char	*res = NULL;

	splited = ft_split(paths, ':');
	while (splited[index])
	{
		slash = ft_strjoin(splited[index++], "/");
		if (!slash)
			return free_split(splited);
		full_path = ft_strjoin(slash, command);
		free(slash);
		if (!full_path)
			return free_split(splited);
		if (access(full_path, X_OK) == 0)
		{
			res = full_path;
			break;
		}
		free(full_path);
	}
	free_split(splited);
	return res;
}

int	split_length(char **spl)
{
	int	index;

	index = 0;
	while (spl[index])
		index++;
	return (index);
}


void	first_command(char *filename, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		input;

	splitted = ft_split(command, ' ');
	if (!splitted)
		exit(1);
	
	path = find_path(splitted[0], env[14]);
	if (!path)
		exit(1);

	input = open(filename, O_RDONLY);
	if (input)
	{
		dup2(input, STDIN_FILENO);
	}

	dup2(output, STDOUT_FILENO);
	if (execve(path, splitted, env))
		exit(1);
}

void	second_command(int input, char *command, char **env, char *filename)
{
	char	**splitted;
	char	*path;
	int		output;

	splitted = ft_split(command, ' ');
	if (!splitted)
		exit(-1);

	path = find_path(splitted[0], env[14]);
	if (!path)
		exit(-1);

	output = open(filename, O_WRONLY | O_CREAT, 0777);
	if (output)
	{
		dup2(output, STDOUT_FILENO);
	}

	dup2(input, STDIN_FILENO);
	if (execve(path, splitted, env))
		exit(-1);
}

int manage(char **argv, char **env)
{
	(void) argv, (void)env;
	int	pid;
	int fd[2];
	int status = 0;
	// int res;

	char **del1 = ft_split(argv[2], ' ');
	char **del2 = ft_split(argv[3], ' ');

	if (!find_path(del1[0], env[14]) || !find_path(del2[0], env[14]))
		exit(1);


	if (pipe(fd))
		return printf("Error\n");
	pid = fork();
	if (pid < 0)
	{
		printf("Error al hacer fork.\n");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	if (pid == 0)
	{
		/* Hijo */
		close(fd[0]);
		first_command(argv[1], argv[2], env, fd[1]);
	}
	else
	{
		/* Padre */
		//waitpid(0, &status, 0);
		wait(NULL);
		if (status == -1)
		{
			printf("Ce fini\n");
			exit(1);
		}
		close(fd[1]);
		second_command(fd[0], argv[3], env, argv[4]);
	}
	return 0;
}

void leaks()
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char *env[])
{	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	// int index = 0;
	// while (env[index])
	// 	printf("%s\n", env[index++]);

	return manage(argv, env);


}










	/* int	index = -1;
	while (env[++index])
		printf("(%d) %s\n", index, env[index]);*/

	/*
		char **test = malloc(5 * sizeof(char *));
		int fd = open("res.txt", O_WRONLY | O_CREAT, 0777);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		test[0] = strdup("ping");
		test[1] = strdup("8.8.8.8");
		test[2] = strdup("-c 2");
		test[3] = NULL;
		execve("/sbin/ping", test, env);
	*/