/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:14:06 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/01 09:14:06 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../inc/pipex.h"
#include <sys/errno.h>

void	input_command(char *input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		fd;

	splitted = divide_arguments(command);
	if (!splitted)
		exit_error(1, -1, NULL, NULL);
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		exit_error(1, -1, NULL, splitted);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		exit_error(1, -1, path, splitted);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(output, STDOUT_FILENO);
	close(output);
	if (execve(path, splitted, env) == -1)
		exit_error(1, -1, path, splitted);
}

void	output_command(int input, char *command, char **env, char *output)
{
	char	**splitted;
	char	*path;
	int		fd;

	splitted = divide_arguments(command);
	if (!splitted)
		exit_error(1, 1, NULL, NULL);
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		exit_error(1, 1, NULL, splitted);
	fd = open(output, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		exit_error(1, 1, path, splitted);
	dup2(input, STDIN_FILENO);
	close (input);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	if (execve(path, splitted, env) == -1)
		exit_error(1, 1, path, splitted);
}

int	manage(char **argv, char **env, char *input, char *output)
{
	int	pid;
	int	fd[2];
	int	status;

	if (pipe(fd))
		exit_error(1, 1, NULL, NULL);
	pid = fork();
	if (pid < 0)
		exit_error(1, 1, NULL, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		input_command(input, argv[2], env, fd[1]);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 255)
			exit_error(0, 1, NULL, NULL);
		close(fd[1]);
		output_command(fd[0], argv[3], env, output);
	}
	exit(0);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		return (write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40));
	return (manage(argv, env, argv[1], argv[argc - 1]));
}
