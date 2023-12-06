/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/05 20:01:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Gestion variada */
#include <stdio.h>
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

void	*free_array(char **arr);
void	exit_error(int flag, int end, char *path, char **arg);

#endif