/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:09:44 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/01 09:12:38 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	get_path_index(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (!strncmp(env[index], "PATH", 4))
			return index;
		index++;
	}
	return -1;
}

char *find_path(char *command, char *paths)
{
	char	*slash;
	char	*full_path;
	char	**splited;
	int		index = 0;
	char	*res = NULL;

	splited = ft_split(paths, ':');
	while (splited[index])
	{
		slash = ft_strjoin(splited[index++], "/");
		if (!slash)
			return free_split(splited);
		full_path = ft_strjoin(slash, command);
		free(slash);
		if (!full_path)
			return free_split(splited);
		if (access(full_path, X_OK) == 0)
		{
			res = full_path;
			break;
		}
		free(full_path);
	}
	free_split(splited);
	return res;
}