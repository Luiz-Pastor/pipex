/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:04:14 by lpastor-          #+#    #+#             */
/*   Updated: 2024/06/07 12:18:25 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static void	init_fields(t_pipex *data)
{
	data->path = NULL;
	data->splitted = NULL;
}

static void	get_data(t_pipex *data, char *command, int fd1, int fd2)
{
	int	index;

	data->splitted = divide_arguments(command);
	if (!data->splitted)
	{
		close_files(fd1, fd2);
		exit_child(MEMORY_PROBLEM, NULL, data);
	}
	if (is_full_path(data->splitted[0]))
		data->path = ft_strdup(data->splitted[0]);
	else
	{
		index = get_path_index(data->env);
		if (index == -1)
		{
			data->path = ft_strdup(data->splitted[0]);
			return ;
		}
		data->path = find_path(data->splitted[0], data->env[index]);
		if (!data->path)
		{
			close_files(fd1, fd2);
			exit_child(MEMORY_PROBLEM, command, data);
		}
	}
}

void	input_command(t_pipex *data, char *command)
{
	int		fd;

	init_fields(data);
	fd = open(data->input, O_RDONLY);
	if (fd < 0)
	{
		close(data->current_pipe[1]);
		exit_child(NO_FILE, data->input, data);
	}
	get_data(data, command, fd, data->current_pipe[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(data->current_pipe[1], STDOUT_FILENO);
	close(data->current_pipe[1]);
	if (execve(data->path, data->splitted, data->env) == -1)
		exit_child(COMMAND_PROBLEM, data->path, data);
}

void	middle_command(t_pipex *data, char *command)
{
	init_fields(data);
	get_data(data, command, data->last_pipe, data->current_pipe[1]);
	dup2(data->last_pipe, STDIN_FILENO);
	close(data->last_pipe);
	dup2(data->current_pipe[1], STDOUT_FILENO);
	close(data->current_pipe[1]);
	if (execve(data->path, data->splitted, data->env) == -1)
		exit_child(COMMAND_PROBLEM, data->path, data);
}

void	output_command(t_pipex *data, char *command)
{
	int		fd;

	init_fields(data);
	if (!data->is_heredoc)
		fd = open(data->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(data->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		close(data->last_pipe);
		exit_child(NO_FILE, data->output, data);
	}
	get_data(data, command, data->last_pipe, fd);
	dup2(data->last_pipe, STDIN_FILENO);
	close (data->last_pipe);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	if (execve(data->path, data->splitted, data->env) == -1)
		exit_child(COMMAND_PROBLEM, data->path, data);
}
