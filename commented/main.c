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

/* TODO: cambiar printf por write*/

#include <stdio.h>
#include <string.h>
#include "../inc/pipex.h"
#include <sys/errno.h>

void	input_command(char *input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;
	int		fd;

	/* Dividimos los argumentos ([comando] [argumento1] [argumento2] [...]) */
	splitted = divide_arguments(command);
	if (!splitted)
		exit_error(1, -1, NULL, NULL);

	/* Buscamos el path del comando a ejecutar */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		exit_error(1, -1, NULL, splitted);

	/* Rederigimos la entrada estandar */
	fd = open(input, O_RDONLY);
	if (fd < 0)
		exit_error(1, -1, path, splitted);

	/* Rederigimos la entrada */
	dup2(fd, STDIN_FILENO);
	close(fd);

	/* Rederigimos la salida */
	dup2(output, STDOUT_FILENO);
	close(output);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
		exit_error(1, -1, path, splitted);
}

void	output_command(int input, char *command, char **env, char *output)
{
	char	**splitted;
	char	*path;
	int		fd;

	/* Separamos los argumentos ([comando] [arg1] [arg2] [...]) */
	splitted = divide_arguments(command);
	if (!splitted)
		exit_error(1, 1, NULL, NULL);

	/* Buscamos la ruta del comando */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		exit_error(1, 1, NULL, splitted);

	/* Abrimos el archivo de salida */
	fd = open(output, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		exit_error(1, 1, path, splitted);

	/* Rederigimos la entrada estandar */
	dup2(input, STDIN_FILENO);
	close (input);

	/* Rederigimos la salida estandar */
	dup2(fd, STDOUT_FILENO);
	close (fd);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
		exit_error(1, 1, path, splitted);
}

int	manage(char **argv, char **env, char *input, char *output)
{
	int	pid;
	int	fd[2];
	int	status;

	/* Abrimos el pipe para escribir el resultado del primer comando */
	if (pipe(fd))
		exit_error(1, 1, NULL, NULL);

	/* Ejecutamos proceso hijo */
	pid = fork();
	if (pid < 0)
		exit_error(1, 1, NULL, NULL);

	if (pid == 0)
	{
		/* Proceso hijo */
		/* Cerramos la lectura del pipe */
		close(fd[0]);

		/* Ejecutamos el primer comando */
		input_command(input, argv[2], env, fd[1]);
	}
	else
	{
		/* Proceso padre */
		/* Esperamos a que acabe el proceso hijo */
		waitpid(-1, &status, 0);

		/* Miramos si el hijo ha devuelto error */
		if (WEXITSTATUS(status) == 255)
			exit_error(0, 1, NULL, NULL);

		/* Cerramos la escritura del pipe, no la usamos*/
		close(fd[1]);

		/* Ejecutamos el segundo comando */
		output_command(fd[0], argv[3], env, output);
	}
	exit(0);
}

int	main(int argc, char *argv[], char *env[])
{	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	return (manage(argv, env, argv[1], argv[argc - 1]));
}
