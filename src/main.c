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

int	manage(char **argv, char **env, char *input, char *output)
{
	int	pid[2];
	int	fd[2];
	int status;

	if (pipe(fd))
		exit_error(1, 1, NULL, NULL);
	pid[0] = fork();
	if (pid[0] < 0)
		exit_error(1, 1, NULL, NULL);
	if (!pid[0])
	{
		close(fd[0]);
		input_command(input, argv[2], env, fd[1]);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		exit_error(1, 1, NULL, NULL);
	if (!pid[1])
	{
		close(fd[1]);
		output_command(fd[0], argv[3], env, output);
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	printf("==> %d\n", WEXITSTATUS(status));
	exit(1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		return (write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40));
	return (manage(argv, env, argv[1], argv[argc - 1]));
}
