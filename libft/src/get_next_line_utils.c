/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:02:16 by lpastor-          #+#    #+#             */
/*   Updated: 2023/11/02 08:49:56 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
		index++;
	return (index);
}

char	*gnl_cpy(char *data)
{
	size_t	index;
	char	*cpy;

	index = 0;
	if (!data)
		return (NULL);
	cpy = (char *) malloc(gnl_strlen(data) + 1);
	if (!cpy)
		return (NULL);
	while (data[index])
	{
		cpy[index] = data[index];
		index++;
	}
	cpy[index] = '\0';
	return (cpy);
}

int	gnl_find_ch(char *data, char ch)
{
	size_t	index;

	index = 0;
	if (!data)
		return (0);
	while (data[index] && data[index] != ch)
		index++;
	if (data[index] == ch)
		return (1);
	return (0);
}

void	*gnl_free(void **memory)
{
	if (!memory || !(*memory))
		return (NULL);
	free(*memory);
	*memory = NULL;
	return (NULL);
}

char	*add_line(char *data, char *add)
{
	char	*new;
	size_t	index_in;
	size_t	index_new;

	index_in = 0;
	index_new = 0;
	new = (char *) malloc(gnl_strlen(data) + gnl_strlen(add) + 1);
	if (!new)
	{
		gnl_free((void **)&add);
		return (gnl_free((void **)&data));
	}
	while (data && data[index_in])
		new[index_new++] = data[index_in++];
	index_in = 0;
	while (add[index_in])
		new[index_new++] = add[index_in++];
	new[index_new] = '\0';
	if (data)
		gnl_free((void **)&data);
	gnl_free((void **)&add);
	return (new);
}
