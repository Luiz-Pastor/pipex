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

#include "../inc/pipex.h"

#define BAD_ARGV "Usage: ./pipex infile cmd1 cmd2 outfile\n"

void	first_command(t_pipex *data)
{
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		exit_parent(data->fd);
	if (!data->pid[0])
	{
		close(data->fd[0]);
		input_command(data, data->argv[2]);
	}
}

void	last_command(t_pipex *data)
{
	data->pid[1] = fork();
	if (data->pid[1] < 0)
		exit_parent(data->fd);
	if (!data->pid[1])
	{
		close(data->fd[1]);
		output_command(data, data->argv[3]);
	}
}

int	manage(t_pipex *data)
{
	int	status[2];

	if (pipe(data->fd))
		exit_parent(NULL);
	first_command(data);
	last_command(data);
	close_pipe(data->fd);
	wait_childs(data->pid, status);
	exit(WEXITSTATUS(status[1]));
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	data;

	if (argc != 5)
		return (write(1, BAD_ARGV, ft_strlen(BAD_ARGV)));
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	data.input = argv[1];
	data.output = argv[argc - 1];
	return (manage(&data));
}
