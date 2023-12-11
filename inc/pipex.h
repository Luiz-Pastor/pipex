/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/11 10:53:00 by lpastor-         ###   ########.fr       */
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

int		get_path_index(char **env);
char	*find_path(char *command, char *paths);
char	**divide_arguments(char *command);

int		ft_isspace(char ch);
void	*free_array(char **arr);
void	exit_error(int flag, int end, char *path, char **arg);
char	*stract_word(char *string, char it, int *index, int inc);

/* Bonus */
char	*here_doc(char *delimiter);
void	check_heredoc(char **argv);

#endif