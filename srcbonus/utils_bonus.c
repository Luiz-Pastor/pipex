/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:54:55 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/11 08:54:55 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	*free_array(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return (NULL);
	while (arr[index])
		free(arr[index++]);
	free(arr);
	return (NULL);
}

int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
		return (1);
	if (ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

char	*stract_word(char *string, char it, int *index, int inc)
{
	char	*new;
	int		start;

	start = *index;
	(*index)++;
	while (string[*index] && string[*index] != it)
		(*index)++;
	if (inc)
		new = ft_substr(string, start + 1, (*index) - start - 1);
	else
		new = ft_substr(string, start, (*index) - start);
	return (new);
}

void	close_pipe(int *fd)
{
	if (!fd)
		return ;
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

void	wait_childs(t_pipex *data)
{
	pid_t	current_pid;
	int		status;

	while (1)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid <= 0)
			break ;
		if (current_pid == data->final_pid)
		{
			if (WEXITSTATUS(status))
				data->last_status = WEXITSTATUS(status);
		}
	}
}
