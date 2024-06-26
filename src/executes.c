/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:04:14 by lpastor-          #+#    #+#             */
/*   Updated: 2024/06/07 12:13:52 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	init_fields(t_pipex *data)
{
	data->path = NULL;
	data->splitted = NULL;
}

static void	get_data(t_pipex *data, char *command, int fd)
{
	int	index;

	data->splitted = divide_arguments(command);
	if (!data->splitted)
		exit_child(MEMORY_PROBLEM, NULL, fd, data);
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
			exit_child(MEMORY_PROBLEM, command, fd, data);
	}
}

void	input_command(t_pipex *data, char *command)
{
	int		fd;

	init_fields(data);
	fd = open(data->input, O_RDONLY);
	if (fd < 0)
		exit_child(NO_FILE, data->input, -1, data);
	get_data(data, command, fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	if (execve(data->path, data->splitted, data->env) == -1)
		exit_child(COMMAND_PROBLEM, data->path, -1, data);
}

void	output_command(t_pipex *data, char *command)
{
	int		fd;

	init_fields(data);
	fd = open(data->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit_child(NO_FILE, data->output, -1, data);
	get_data(data, command, fd);
	dup2(data->fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (data->fd[0]);
	close (fd);
	if (execve(data->path, data->splitted, data->env) == -1)
		exit_child(COMMAND_PROBLEM, data->path, -1, data);
}
