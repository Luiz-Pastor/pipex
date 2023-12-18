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

#include <stdio.h>
#include <string.h>
#include "../inc/pipex_bonus.h"
#include <sys/errno.h>

static void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	data->argc = argc;
	data->env = env;
	data->pids = NULL;
	data->returns = NULL;

	if (!ft_strcmp(argv[1], "here_doc"))
	{
		data->cmds = argc - 4 - 2;
		data->argv = argv + 1;
	}
	else
	{
		data->cmds = argc - 3 - 2;
		data->argv = argv;
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

}

int manage(t_pipex *data)
{
	int	count;

	count = 1;
	first_command(data);
	while (count < data->cmds)
	{

	}
	last_command(data);
}

/* NOTE: Quedarse con ultimo pid */
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