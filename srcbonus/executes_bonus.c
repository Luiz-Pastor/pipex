/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:04:14 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/20 20:00:13 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/* Cerrar los archivos al acabar */
void	input_command(char *input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		fd;
	int		index;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		exit_child(NO_FILE, input, NULL, NULL);
	splitted = divide_arguments(command);
	if (!splitted)
		exit_child(MEMORY_PROBLEM, NULL, NULL, NULL);
	index = get_path_index(env);
	if (index == -1)
		exit_child(ENV_PROBLEM, NULL, NULL, splitted);
	path = find_path(splitted[0], env[index]);
	if (!path)
		exit_child(NO_COMMAND, command, NULL, splitted);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(output, STDOUT_FILENO);
	close(output);
	if (execve(path, splitted, env) == -1)
		exit_child(COMMAND_PROBLEM, path, path, splitted);
}

void	middle_command(int input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		index;

	splitted = divide_arguments(command);
	if (!splitted)
		exit_child(MEMORY_PROBLEM, NULL, NULL, NULL);
	index = get_path_index(env);
	if (index == -1)
		exit_child(ENV_PROBLEM, NULL, NULL, splitted);
	path = find_path(splitted[0], env[index]);
	if (!path)
		exit_child(NO_COMMAND, command, NULL, splitted);
	dup2(input, STDIN_FILENO);
	close(input);
	dup2(output, STDOUT_FILENO);
	close(output);
	if (execve(path, splitted, env) == -1)
		exit_child(COMMAND_PROBLEM, path, path, splitted);
}

void	output_command(int input, char *command, char **env, t_pipex *data)
{
	char	**splitted;
	char	*path;
	int		fd;
	int		index;

	if (!data->is_heredoc)
		fd = open(data->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(data->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		exit_child(NO_FILE, data->output, NULL, NULL);
	splitted = divide_arguments(command);
	if (!splitted)
		exit_child(MEMORY_PROBLEM, NULL, NULL, NULL);
	index = get_path_index(env);
	if (index == -1)
		exit_child(ENV_PROBLEM, NULL, NULL, splitted);
	path = find_path(splitted[0], env[index]);
	if (!path)
		exit_child(NO_COMMAND, command, NULL, splitted);
	dup2(input, STDIN_FILENO);
	close (input);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	if (execve(path, splitted, env) == -1)
		exit_child(COMMAND_PROBLEM, path, path, splitted);
}
