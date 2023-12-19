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

void	first_command(t_pipex *data)
{
	pid_t	pid;

	if (pipe(data->current_pipe) < 0)
		exit_parent(NULL);
	pid = fork();
	if (pid < 0)
		exit_parent(data->current_pipe);
	data->final_pid = pid;
	if (!pid)
	{
		close(data->current_pipe[0]);
		input_command(data->input, data->argv[1], data->env, data->current_pipe[1]);
	}
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
		if (!current_pid)
		{
			close(data->current_pipe[0]);
			middle_command(data->last_pipe, data->argv[index + 1], data->env, data->current_pipe[1]);
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

	pid = fork();
	if (pid < 0)
	{
		close(data->last_pipe);
		exit_parent(NULL);
	}
	data->final_pid = pid;
	if (!pid)
		output_command(data->last_pipe, data->argv[data->argc - 3], data->env, data->output);
	close(data->last_pipe);
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