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
	int	status[2];

	if (pipe(fd))
		exit_parent(NULL);
	pid[0] = fork();
	if (pid[0] < 0)
		exit_parent(fd);
	if (!pid[0])
	{
		close(fd[0]);
		input_command(input, argv[2], env, fd[1]);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		exit_parent(fd);
	if (!pid[1])
	{
		close(fd[1]);
		output_command(fd[0], argv[3], env, output);
	}
	close_pipe(fd);
	wait_childs(pid, status);
	exit(WEXITSTATUS(status[1]));
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	int		count;

	count = 0;
	if (argc < 5)
		return (write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40));
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		input = here_doc(argv[2]);
		count = 1;
	}
	else
		input = argv[1];
	return (manage(argv + count, env, input, argv[argc - 1]));
}
