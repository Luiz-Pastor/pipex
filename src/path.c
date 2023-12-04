/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:09:44 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/04 10:41:38 by lpastor-         ###   ########.fr       */
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

	printf("11 # %s #\n", command);
	splited = ft_split(paths + 5, ':');
	printf("11 # %s #\n", command);
	while (splited[index])
	{
		slash = ft_strjoin(splited[index++], "/");
		if (!slash)
			return free_split(splited);
		printf("## %s ##\n", command);
		full_path = ft_strjoin(slash, command);
		printf("## %s ##\n\n", command);
		free(slash);
		if (!full_path)
			return free_split(splited);
		// printf("> %s\n> %s\n\t> %s\n", slash, command, full_path);
		// printf("> %s\n", full_path);
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
