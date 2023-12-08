/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:09:44 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/08 00:41:39 by luiz_ubuntu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

int	get_path_index(char **env)
{
	int	index;

	/* Iteramos sobre todas las strings de `env`, buscando la que contiene `PATHS` */
	index = 0;
	while (env[index])
	{
		if (!strncmp(env[index], "PATH", 4))
			return (index);
		index++;
	}
	return (-1);
}

static char	*get_full_path(char *path, char *command)
{
	char	*slash;
	char	*full_path;

	/* Unimos la ruta con una '/' */
	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
	
	/* Unimos la ruta al comando */
	full_path = ft_strjoin(slash, command);
	free(slash);
	return (full_path);
}

char	*find_path(char *command, char *paths)
{
	char	*full_path;
	char	**splited;
	int		index;
	char	*res;

	index = 0;
	res = NULL;

	/* Miramos si el comando nos lo pasan con ruta */
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));

	/* Dividimos la variable ed PATH por ':'*/
	splited = ft_split(paths + 5, ':');

	/* Miramos todas las posibles combinaciones del comando */
	while (splited[index])
	{
		/* Unimos path[i] + comando */
		full_path = get_full_path(splited[index++], command);
		if (!full_path)
			return (free_split(splited));
		
		/* Si existe, paramos el bucle */
		if (access(full_path, X_OK) == 0)
		{
			res = full_path;
			break ;
		}
		free(full_path);
	}
	free_split(splited);

	/* Devolvemos o la ruta del comando o NULL */
	return (res);
}
