/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:08:53 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/08 00:56:49 by luiz_ubuntu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

static char	*get_command(char *command)
{
	int	i;

	i = 0;
	while (command && command[i] && !ft_isspace(command[i]))
		i++;
	return ft_substr(command, 0, i);
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
	free(arguments);
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
		if (!arguments)
			return (free(new), NULL);
	}
	if (!arguments)
		arguments = ft_calloc(sizeof(char *), 1);
	return arguments;
}

void	move_last_first(char **arguments)
{
	int	index;
	char *aux;

	/* Iteramos hasta llegar al final */
	index = 0;
	while (arguments[index])
		index++;

	index--;
	
	/* Vamos moviendo el ultimo elemento una posicion a la izquierda */
	while (index > 0)
	{
		aux = arguments[index];
		arguments[index] = arguments[index - 1];
		arguments[index - 1] = aux;
		index--;
	}
}

char	**divide_arguments(char *command)
{
	char	*cmd;
	char	**arguments;
	int		index;

	/* Primero nos saltamos todos los espacios/tabulaciones */
	index = 0;
	while (ft_isspace(command[index]))
		index++;

	/* Guardamos el comando, primera palabra de los argumentos*/
	cmd = get_command(&command[index]);
	if (!cmd)
		return NULL;
	
	/* Guardamos el resto de argumentos */
	index += ft_strlen(cmd);
	arguments = get_arguments(&command[index]);
	if (!arguments)
	{
		free(cmd);
		return NULL;
	}

	/* Añadimos el comando como primera posicion de la array de argumentos */
	arguments = add_argument(arguments, cmd);
	move_last_first(arguments);
	return arguments;
}
