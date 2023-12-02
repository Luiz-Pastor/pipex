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

void	select_error(int status)
{
	if (status == PIPE)
		perror("Pipe");
	else if (status == FORK)
		perror("Fork");
	else if (status == MEMORY)
		perror("Memory");
	else if (status == FILE_OPEN)
		perror("File");
	else if (status == PATH)
		perror("Path");
	else if (status == COMMAND)
		perror("Command");
	else
		return ;
	exit(status);
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
	splitted = ft_split(command, ' ');
	if (!splitted)
		select_error(MEMORY);
	
	/* Buscamos el path del comando a ejecutar */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		select_error(PATH);

	/* Rederigimos la entrada estandar */
	dup2(input, STDIN_FILENO);
	close(input);

	/* Rederigimos la salida estandar */
	dup2(output, STDOUT_FILENO);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env))
		select_error(COMMAND);
}

void	second_command(int input, char *command, char **env, int output)
{
	char	**splitted;
	char	*path;

	/* Separamos los argumentos ([comando] [arg1] [arg2] [...]) */
	splitted = ft_split(command, ' ');
	if (!splitted)
		select_error(MEMORY);

	/* Buscamos la ruta del comando */
	path = find_path(splitted[0], env[get_path_index(env)]);
	if (!path)
		select_error(PATH);

	/* Rederigimos la entrada estandar */
	dup2(input, STDIN_FILENO);
	close (input);

	/* Rederigimos la salida estandar */
	dup2(output, STDOUT_FILENO);
	close (output);

	/* Ejecutamos el comando */
	if (execve(path, splitted, env))
		select_error(COMMAND);
}

int manage(char **argv, char **env, int input, int output)
{
	(void) argv, (void)env;
	int	pid;
	int fd[2];
	int status;

	if (pipe(fd))
		select_error(PIPE);

	pid = fork();
	if (pid < 0)
		select_error(FORK);
	
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
		select_error(status);

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

	// int index = 0;
	// while (env[index])
	// 	printf("%s\n", env[index++]);

	input = open(argv[1], O_RDONLY);
	output = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
	if (input < 0 || output < 0)
		select_error(FILE_OPEN);

	return manage(argv, env, input, output);


}










	/* int	index = -1;
	while (env[++index])
		printf("(%d) %s\n", index, env[index]);*/

	/*
		char **test = malloc(5 * sizeof(char *));
		int fd = open("res.txt", O_WRONLY | O_CREAT, 0777);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		test[0] = strdup("ping");
		test[1] = strdup("8.8.8.8");
		test[2] = strdup("-c 2");
		test[3] = NULL;
		execve("/sbin/ping", test, env);
	*/