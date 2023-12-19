/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:56:47 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/19 09:24:28 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	check_heredoc(t_pipex *data)
{
	if (!data->is_heredoc)
		return ;
	unlink(data->input);
	free(data->input);
}

int	read_data(int fd, char *delimiter)
{
	char	*buffer;
	char	*full_delimiter;

	full_delimiter = ft_strjoin(delimiter, "\n");
	if (!full_delimiter)
		return (0);
	buffer = get_next_line(0);
	while (buffer && ft_strcmp(buffer, full_delimiter))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(0);
	}
	if (buffer)
		free(buffer);
	free(full_delimiter);
	return (1);
}

char	*here_doc(char *delimiter)
{
	int		fd;
	char	*path;
	int		res;

	if (!delimiter)
		return (NULL);
	path = ft_calloc(16, sizeof(char));
	if (!path)
		return (NULL);
	ft_strcpy(path, "/tmp/pipex.log");
	fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		free(path);
		return (NULL);
	}
	res = read_data(fd, delimiter);
	close(fd);
	if (!res)
		return (NULL);
	return (path);
}
