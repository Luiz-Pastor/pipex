/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:53:01 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:59 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	length = ft_strlen(s);
	return (write(fd, s, length));
}

/*
	****************************************
	* void	ft_putstr_fd(char *s, int fd)
	* {
	* 	size_t	index;
	*
	* 	index = 0;
	* 	if (!s)
	* 		return ;
	* 	while (s[index])
	* 		write(fd, &s[index++], 1);
	* }
	****************************************
	* void	ft_putstr_fd(char *s, int fd)
	* {
	* 	size_t	index;
	*
	* 	index = 0;
	* 	if (!s)
	* 		return ;
	* 	while (s[index])
	* 		ft_putchar_fd(s[index++], fd);
	* }
	****************************************
*/
