/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:55:21 by luiz_ubuntu       #+#    #+#             */
/*   Updated: 2023/12/18 13:00:53 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_child(int event, char *content, char *path, char **arguments)
{
	if (event == NO_FILE)
		perror(content);
	else if (event == NO_COMMAND)
	{
		write(1, content, ft_strlen(content));
		write(1, ": command not found\n", 21);
		exit(127);
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
