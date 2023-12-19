/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:23:59 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/19 08:32:05 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	init_child(t_pipex *data)
{
	pid_t	current_pid;

	if (pipe(data->current_pipe))
	{
		close(data->last_pipe);
		exit_parent(NULL);
	}
	current_pid = fork();
	if (current_pid < 0)
	{
		close(data->last_pipe);
		exit_parent(data->current_pipe);
	}
	return (current_pid);
}

void	first_command(t_pipex *data)
{
	pid_t	pid;
	char	*input;
	int		output;

	if (pipe(data->current_pipe) < 0)
		exit_parent(NULL);
	pid = fork();
	if (pid < 0)
		exit_parent(data->current_pipe);
	if (!pid)
	{
		close(data->current_pipe[0]);
		input = data->input;
		output = data->current_pipe[1];
		input_command(input, data->argv[1], data->env, output);
	}
	data->last_pipe = data->current_pipe[0];
	close(data->current_pipe[1]);
}

void	child_command(t_pipex *data)
{
	pid_t	current_pid;
	int		index;
	int		input;
	int		output;

	index = 0;
	while (index < data->cmds)
	{
		current_pid = init_child(data);
		if (!current_pid)
		{
			close(data->current_pipe[0]);
			input = data->last_pipe;
			output = data->current_pipe[1];
			middle_command(input, data->argv[index + 1], data->env, output);
		}
		close(data->last_pipe);
		data->last_pipe = data->current_pipe[0];
		close(data->current_pipe[1]);
		index++;
	}
}

void	last_command(t_pipex *data)
{
	pid_t	pid;
	int		input;
	char	*output;

	pid = fork();
	if (pid < 0)
	{
		close(data->last_pipe);
		exit_parent(NULL);
	}
	data->final_pid = pid;
	if (!pid)
	{
		input = data->last_pipe;
		output = data->output;
		output_command(input, data->argv[data->argc - 3], data->env, output);
	}
	close(data->last_pipe);
}
