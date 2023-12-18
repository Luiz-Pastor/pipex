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

#include "../inc/pipex_bonus.h"

static void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	data->argc = argc;
	data->argv = argv + 1;
	data->env = env;
	
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		data->cmds = argc - 6;
		data->argv = argv + 2;
		data->is_heredoc = 1;
	}
	else
	{
		data->cmds = argc - 5;
		data->is_heredoc = 0;
	}
}

static void	init_files(t_pipex *data, char *infile, char *outfile)
{
	data->input = infile;
	data->output = outfile;
}

/*int	manage(t_pipex *data)
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
		input_command(data->input, data->argv[2], data->env, fd[1]);
	}
	pid[1] = fork(); 
	if (pid[1] < 0)
		exit_parent(fd);
	if (!pid[1])
	{
		close(fd[1]);
		output_command(fd[0], data->argv[3], data->env, data->output);
	}
	close_pipe(fd);
	wait_childs(pid, status);
	exit(WEXITSTATUS(status[1]));
}*/

void	first_command(t_pipex *data)
{
	pid_t	pid;

	/* Creamos el pipe, y lo guardamos */
	if (pipe(data->current_pipe) < 0)
		exit_parent(NULL);
	
	/* Obtenemos el primer proceso para el primer hijo */
	pid = fork();
	if (pid < 0)
		exit_parent(data->current_pipe);
	
	/* Nos guardamos el pid del comando, por si fuera el último */
	data->final_pid = pid;
	if (!pid)
	{
		/* Proceso hijo. Cerramos el pipe de lectura y ejecutamos el comando */
		close(data->current_pipe[0]);

		// printf("=> First input: [%s]\n", data->input);
		// printf("=> Command: [%s]\n", data->argv[1]);
		// printf("=> Env: [%p]\n", data->env);
		// printf("=> Output: [%d]\n", data->current_pipe[1]);

		input_command(data->input, data->argv[1], data->env, data->current_pipe[1]);
	}

	/* Padre. Cerramos le pipe de escritura y nos guardamos el de lectura para los siguientes hijos */
	data->last_pipe = data->current_pipe[0];
	close(data->current_pipe[1]);
}

void	child_command(t_pipex *data)
{
	pid_t	current_pid;
	int		index;

	index = 0;
	while (index < data->cmds)
	{
		// printf("\t=> Current command (%d): [%s]\n", index, data->argv[index + 2]);
		if (pipe(data->current_pipe))
		{
			close(data->last_pipe);
			exit_parent(NULL);
		}
		current_pid = fork();
		if (current_pid < 0)
			exit_parent(data->current_pipe);
		if (!current_pid)
		{
			/* Se ejecuta el comando intermedio */
			/* Cerramos la entrada de lectura */
			close(data->current_pipe[0]);
			middle_command(data->last_pipe, data->argv[index + 1], data->env, data->current_pipe[1]);
		}

		data->last_pipe = data->current_pipe[0];
		close(data->current_pipe[1]);
		index++;
	}
}

void	last_command(t_pipex *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(data->last_pipe);
		exit_parent(NULL);
	}
	data->final_pid = pid;
	if (!pid)
	{
		// printf("# Infile: [%d]\n", data->last_pipe);
		// printf("# Last command: [%s]\n", data->argv[data->argc - 3]);
		// printf("# Env: [%p]\n", data->env);
		// printf("# Outfile: [%s]\n", data->output);

		output_command(data->last_pipe, data->argv[data->argc - 3], data->env, data->output);
	}
}

int manage(t_pipex *data)
{
	first_command(data);
	check_heredoc(data);
	child_command(data);
	last_command(data);

	wait_childs(data);

	exit(data->last_status);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	t_pipex	data;

	if (argc < 5)
		return (write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40));
	if (!ft_strcmp(argv[1], "here_doc"))
		input = here_doc(argv[2]);
	else
		input = argv[1];
	init_data(&data, argc, argv, env);
	init_files(&data, input, argv[argc - 1]);
	return (manage(&data));
}
//return (manage(argv + count, env, input, argv[argc - 1]));