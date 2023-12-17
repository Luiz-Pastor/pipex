/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:04:14 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/17 12:04:40 by luiz_ubuntu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	input_command(char *input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		fd;
	int		index;

	/* Dividimos el comando con sus argumentos */
	splitted = divide_arguments(command);
	if (!splitted)
		exit_child(MEMORY_PROBLEM, NULL, NULL, NULL);

	/* Conseguimos el índice de la parte en la que este las variables del PATH, y conseguimos el path completo del comando */
	index = get_path_index(env);
	if (index == -1)
		exit_child(ENV_PROBLEM, NULL, NULL, splitted);
	path = find_path(splitted[0], env[index]);
	if (!path)
		exit_child(NO_COMMAND, command, NULL, splitted);

	/* Abrimos el archivo de entrada */
	fd = open(input, O_RDONLY);
	if (fd < 0)
		exit_child(NO_FILE, input, path, splitted);

	/* Redirigimos las entradas y salidas */
	dup2(fd, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(fd);
	close(output);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
		exit_child(COMMAND_PROBLEM, path, path, splitted);
}

/*void	child_command(int input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;

	splitted = divide_arguments(command);
	if (!splitted)
		exit_error(1, 1, NULL, NULL);
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		exit_error(1, 1, NULL, splitted);
	dup2(input, STDIN_FILENO);
	close (input);
	dup2(output, STDOUT_FILENO);
	close (output);
	if (execve(path, splitted, env) == -1)
		exit_error(1, 1, path, splitted);
}*/

void	output_command(int input, char *command, char **env, char *output)
{
	char	**splitted;
	char	*path;
	int		fd;
	int		index;

	/* Dividimos el comando con sus argumentos */
	splitted = divide_arguments(command);
	if (!splitted)
		exit_child(MEMORY_PROBLEM, NULL, NULL, NULL);

	/* Conseguimos el índice de la parte en la que este las variables del PATH, y conseguimos el path completo del comando */
	index = get_path_index(env);
	if (index == -1)
		exit_child(ENV_PROBLEM, NULL, NULL, splitted);
	path = find_path(splitted[0], env[index]);
	if (!path)
		exit_child(NO_COMMAND, command, NULL, splitted);
	
	/* Abrimos el archivo de entrada */
	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit_child(NO_FILE, output, path, splitted);
	
	/* Redirigimos las entradas y salidas */
	dup2(input, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (input);
	close (fd);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
		exit_child(COMMAND_PROBLEM, path, path, splitted);
}