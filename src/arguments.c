/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:08:53 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/04 10:32:47 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

void	*free_array(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return NULL;
	while (arr[index])
		free(arr[index++]);
	free(arr);
	return NULL;
}

static int	ft_isspace(char ch)
{
	return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\f');
}

static char	*get_command(char *command)
{
	int	i;

	i = 0;
	while (!ft_isspace(command[i]))
		i++;
	return ft_substr(command, 0, i);
}

static char	*stract_word(char *command, char it, int *index, int inc)
{
	char	*new;
	int		start;
	
	start = *index;
	(*index)++;
	while (command[*index] && command[*index] != it)
		(*index)++;
	if (inc)
		new = ft_substr(command, start, (*index) - start + 1);
	else
		new = ft_substr(command, start, (*index) - start);
	(*index)++;
	return new;
}

static char	**add_argument(char **arguments, char *new)
{
	int	length;
	char	**act;

	length = 0;
	while (arguments && arguments[length])
		length++;
		
	act = malloc((length + 2) * sizeof(char *));
	if (!act)
		return free_array(arguments);
	act[length] = new;
	act[length + 1] = NULL;
	while (--length >= 0)
		act[length] = arguments[length];
	return act;
}

static char	**get_arguments(char *command)
{
	int	index;
	char	**arguments;
	char	*new;

	index = 0;
	arguments = NULL;	
	while (command[index])
	{
		while (command[index] && ft_isspace(command[index]))
			index++;
		if (!command[index])
			break;
		if (command[index] != '\'' && command[index] != '\"')
			new = stract_word(command, ' ', &index, 0);
		else
			new = stract_word(command, command[index], &index, 1);
		if (!new)
			return free_array(arguments);
	
		arguments = add_argument(arguments, new);
	}
	return arguments;
}

char	**divide_arguments(char *command)
{
	char	*cmd;
	char	**arguments;
	int		index;

	index = 0;
	while (ft_isspace(command[index]))
		index++;

	cmd = get_command(&command[index]);
	if (!cmd)
		return NULL;

	index += ft_strlen(cmd);
	
	arguments = get_arguments(&command[index]);
	if (!arguments)
	{
		free(cmd);
		return NULL;
	}

	arguments = add_argument(arguments, cmd);
	index = 0;
	while (arguments[index])
		index++;
	
	char *aux;
	aux = arguments[0];
	arguments[0] = arguments[index - 1];
	arguments[index - 1] = aux;

	free(cmd);
	return arguments;
}
