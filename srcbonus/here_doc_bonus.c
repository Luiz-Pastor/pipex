/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz_ubuntu <luiz_ubuntu@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:56:47 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/18 20:20:42 by luiz_ubuntu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	check_heredoc(t_pipex *data)
{
	if (!data->is_heredoc)
		return ;
	unlink("/tmp/pipex.log");
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
	fd = open(path, O_WRONLY | O_CREAT, 0777);
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
