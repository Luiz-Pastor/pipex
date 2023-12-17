/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:55:21 by luiz_ubuntu       #+#    #+#             */
/*   Updated: 2023/12/17 12:46:56 by luiz_ubuntu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_error(int flag, int end, char *path, char **arg)
{
	if (path)
		free(path);
	if (arg)
		free_array(arg);
	if (flag)
		perror("Error");
	exit(end);
}

void	exit_child(int event, char *content, char *path, char **arguments)
{
	if (event == NO_FILE)
		perror(content);
	else if (event == NO_COMMAND)
	{
		write(1, content, ft_strlen(content));
		write(1, ": command not found\n", 21);
	}
	else if (event == COMMAND_PROBLEM)
		perror(content);
	else if (event == ENV_PROBLEM)
		write(1, "Environment error: insufficient information\n", 45);
	else
		perror("Memory error");
	if (path)
		free(path);
	if (arguments)
		free_array(arguments);
	exit(1);
}

void	exit_parent(int *fd)
{
	if (fd)
		close_pipe(fd);
	perror("Error");
	exit(1);
}