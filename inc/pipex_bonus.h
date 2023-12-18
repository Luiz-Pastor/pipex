/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/18 12:50:50 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Gestion variada */
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

/* wait / waitpid */
# include <sys/types.h>
# include <sys/wait.h>

/* Gestion de archivos */
# include <unistd.h>
# include <fcntl.h>

# include "../libft/libft.h"

typedef struct s_pipex t_pipex;
struct s_pipex {
	char	*input;
	char	*output;
	
	int		current_pipe[2];
	int		prev_pipe[2];

	pid_t	*pids;
	int		returns;

	int		argc;
	char	**argv;
	char	**env;
	int		cmds;
};

enum {
	NO_FILE = 0,
	NO_COMMAND,
	COMMAND_PROBLEM,
	MEMORY_PROBLEM,
	ENV_PROBLEM
};

int		get_path_index(char **env);
char	*find_path(char *command, char *paths);
char	**divide_arguments(char *command);

void	input_command(char *input, char *command, char **env, int output);
void	child_command(int input, char *command, char **env, int output);
void	output_command(int input, char *command, char **env, char *output);

int		ft_isspace(char ch);
void	*free_array(char **arr);
void	exit_child(int event, char *content, char *path, char **arguments);
void	exit_parent(int *fd);
char	*stract_word(char *string, char it, int *index, int inc);

void	close_pipe(int *fd);
void	wait_childs(int *pid, int *status);

/* Bonus */
char	*here_doc(char *delimiter);
void	check_heredoc(char **argv);

#endif