/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/17 00:56:34 by luiz_ubuntu      ###   ########.fr       */
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
	
	int		fd_in;
	int		fd_out;

	char	**argv;
	char	**env;
};

enum {
	NONE = 0,
	NO_FILE,
	NO_COMMAND,
	COMMAND_PROBLEM,
	MEMORY_PROBLEM
};

int		get_path_index(char **env);
char	*find_path(char *command, char *paths);
char	**divide_arguments(char *command);

void	input_command(char *input, char *command, char **env, int output);
void	child_command(int input, char *command, char **env, int output);
void	output_command(int input, char *command, char **env, char *output);

int		ft_isspace(char ch);
void	*free_array(char **arr);
void	exit_error(int flag, int end, char *path, char **arg);
char	*stract_word(char *string, char it, int *index, int inc);

/* Bonus */
char	*here_doc(char *delimiter);
void	check_heredoc(char **argv);

#endif