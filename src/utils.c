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

#include "../inc/pipex.h"

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
