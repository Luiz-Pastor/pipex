/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:10:03 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/03 12:37:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Gestion variada */
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

/*
	0 = OK
	1 = Pipe error
	2 = Fork error
	3 = Error de memoria
	4 = No existe/no se puede acceder archivo
	5 = No existe PATH
	6 = Error a ejecutar comando
*/
enum {
	PIPE = 1,
	FORK,
	MEMORY,
	FILE_OPEN,
	PATH,
	COMMAND = -1
};

int		get_path_index(char **env);
char	*find_path(char *command, char *paths);

#endif