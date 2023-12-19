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

int	manage(t_pipex *data)
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
