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
#include "../inc/pipex.h"


void	*del(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return NULL;
	while (arr[index])
		free(arr[index++]);
	free(arr);
	return NULL;
}

void	printCommandInput(char *path, char **arguments, char **env, int mode)
{
	int	index = 0;

	printf("Path: %s\n", path);

	printf("Arguments:\n");
	while (arguments[index])
		printf("\t- [ %s ]\n", arguments[index++]);
	printf("\t[ NULL ]\n");

	if (mode == 0)
		printf("ENV: %p\n", env);
	else
	{
		index = 0;
		while (env[index])
			printf("\t%s\n", env[index++]);
	}
}

// int	split_length(char **spl)
// {
// 	int	index;

// 	index = 0;
// 	while (spl[index])
// 		index++;
// 	return (index);
// }

void	first_command(int input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;

	/* Dividimos los argumentos ([comando] [argumento1] [argumento2] [...])*/
	// splitted = ft_split(command, ' ');
	// if (!splitted)
	// 	exit(-1);

	splitted = divide_arguments(command);
	if (!splitted)
		exit_error();

	/* Buscamos el path del comando a ejecutar */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
	{
		// free_array(splitted);
		exit(-1);
	}

	/* printCommandInput(path, splitted, env, 0); */

	/* Rederigimos la entrada estandar */
	dup2(input, STDIN_FILENO);
	close(input);

	/* Rederigimos la salida estandar */
	dup2(output, STDOUT_FILENO);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
	{
		// free_array(splitted);
		exit(-1);
	}
}

void	second_command(int input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;

	/* Separamos los argumentos ([comando] [arg1] [arg2] [...]) */
	// splitted = ft_split(command, ' ');
	// if (!splitted)
	// 	exit_error();

	splitted = divide_arguments(command);
	if (!splitted)
		exit_error();


	/* Buscamos la ruta del comando */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
	{
		// free_array(splitted);
		exit_error();
	}

	/*printCommandInput(path, splitted, env, 0);*/

	/* Rederigimos la entrada estandar */
	dup2(input, STDIN_FILENO);
	close (input);

	/* Rederigimos la salida estandar */
	dup2(output, STDOUT_FILENO);
	close (output);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env) == -1)
	{
		// free_array(splitted);
		exit_error();
	}
}

int manage(char **argv, char **env, int input, int output)
{
	(void) argv, (void)env;
	int	pid;
	int fd[2];
	int status;

	if (pipe(fd))
		exit_error();

	pid = fork();
	if (pid < 0)
		exit_error();
	
	if (pid == 0)
	{
		/* Cerramos la lectura del pipe */
		close(fd[0]);

		/* Ejecutamos el primer comando */
		first_command(input, argv[2], env, fd[1]);
	}
	else
	{
		/* Esperamos a que acabe el proceso hijo */
		waitpid(-1, &status, 0);

		/* Miramos si el hijo ha devuelto error */
		if (status == -1)
			exit_error();

		/* Cerramos la escritura del pipe, no la usamos*/
		close(fd[1]);

		/* Ejecutamos el segundo comando */
		second_command(fd[0], argv[3], env, output);
	}
	exit(0);
}

int	main(int argc, char *argv[], char *env[])
{	
	int	input;
	int output;
	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	input = open(argv[1], O_RDONLY);
	output = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
	if (input < 0 || output < 0)
		exit_error();

	return manage(argv, env, input, output);
}
