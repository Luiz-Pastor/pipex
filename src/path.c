/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:09:44 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/13 13:09:12 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

int	get_path_index(char **env)
{
	int	index;

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

	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
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
	/* TODO: verificar que el path nos lo pasan completo --> strcmps*/
	splited = ft_split(paths + 5, ':');
	while (splited[index])
	{
		full_path = get_full_path(splited[index++], command);
		if (!full_path)
			return (free_split(splited));
		if (access(full_path, X_OK) == 0)
		{
			res = full_path;
			break ;
		}
		free(full_path);
	}
	free_split(splited);
	return (res);
}
