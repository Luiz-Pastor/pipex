/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 07:54:18 by lpastor-          #+#    #+#             */
/*   Updated: 2023/11/02 08:50:02 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_line(char *data)
{
	char	*line;
	size_t	index;

	index = 1;
	if (!data)
		return (NULL);
	while (data[index - 1] && data[index - 1] != '\n')
		index++;
	if (!data[index - 1])
		return (NULL);
	line = (char *) malloc(index + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (data[index] && data[index] != '\n')
	{
		line[index] = data[index];
		index++;
	}
	line[index] = '\n';
	line[index + 1] = '\0';
	return (line);
}

static char	*delete_line(char *data)
{
	char	*new;
	size_t	index_data;
	size_t	index_new;
	size_t	count;

	index_data = 1;
	index_new = 0;
	if (!data)
		return (NULL);
	while (data[index_data - 1] && data[index_data - 1] != '\n')
		index_data++;
	if (!data[index_data - 1])
		return (data);
	count = gnl_strlen(data) - index_data;
	if (!count)
		return (gnl_free((void **)&data));
	new = (char *) malloc(count + 1);
	if (!new)
		return (gnl_free((void **)&data));
	while (data[index_data])
		new[index_new++] = data[index_data++];
	new[index_new] = '\0';
	gnl_free((void **)&data);
	return (new);
}

static char	*read_file(int fd, char **data)
{
	char	*temp;
	long	length;

	while (1)
	{
		temp = (char *) malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (gnl_free((void **)data));
		length = read(fd, temp, BUFFER_SIZE);
		if (length == 0)
		{
			gnl_free((void **)&temp);
			return (*data);
		}
		if (length < 0)
			return (gnl_free((void **)temp), gnl_free((void **)data));
		temp[length] = '\0';
		*data = add_line(*data, temp);
		if (!*data)
			return (NULL);
		if (gnl_find_ch(*data, '\n'))
			return (*data);
	}
	return (NULL);
}

static char	*change_data(char **data)
{
	char	*line;

	line = get_line(*data);
	if (!line && (*data))
		return (gnl_free((void **)data));
	(*data) = delete_line(*data);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*data[GNL_MAX_FD];
	char		*line;

	if (fd < 0 || fd > GNL_MAX_FD || read(fd, 0, 0) || BUFFER_SIZE < 1)
		return (gnl_free((void **)&data[fd]));
	if (gnl_find_ch(data[fd], '\n'))
		return (change_data(&data[fd]));
	data[fd] = read_file(fd, &data[fd]);
	if (!data[fd])
		return (NULL);
	if (gnl_find_ch(data[fd], '\n'))
		return (change_data(&data[fd]));
	line = gnl_cpy(data[fd]);
	return (gnl_free((void **)&data[fd]), line);
}
