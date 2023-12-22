/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/22 08:08:23 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**env;
	char	*input;
	char	*output;
	int		fd[2];
	int		pid[2];
	char	*path;
	char	**splitted;
}				t_pipex;

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
int		is_full_path(char *path);
void	input_command(t_pipex *data, char *command);
void	output_command(t_pipex *data, char *command);
int		ft_isspace(char ch);
void	*free_array(char **arr);
void	exit_child(int event, char *content, int fd, t_pipex *data);
void	exit_parent(int *fd);
char	*stract_word(char *string, char it, int *index, int inc);
void	close_pipe(int *fd);
void	wait_childs(int *pid, int *status);
char	*here_doc(char *delimiter);
void	check_heredoc(char **argv);

#endif