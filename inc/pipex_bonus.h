/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/20 19:51:06 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/libft.h"

typedef struct s_pipex	t_pipex;
struct s_pipex {
	int		argc;
	char	**argv;
	char	**env;
	char	*input;
	char	*output;	
	int		last_pipe;
	int		current_pipe[2];
	pid_t	final_pid;
	int		last_status;
	int		cmds;
	int		is_heredoc;
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

void	first_command(t_pipex *data);
void	child_command(t_pipex *data);
void	last_command(t_pipex *data);

void	input_command(char *input, char *command, char **env, int output);
void	middle_command(int input, char *command, char **env, int output);
void	output_command(int input, char *command, char **env, t_pipex *data);

int		ft_isspace(char ch);
void	*free_array(char **arr);
void	exit_child(int event, char *content, char *path, char **arguments);
void	exit_parent(int *fd);
char	*stract_word(char *string, char it, int *index, int inc);

void	close_pipe(int *fd);
void	wait_childs(t_pipex *data);

char	*here_doc(char *delimiter);
void	check_heredoc(t_pipex *data);

#endif