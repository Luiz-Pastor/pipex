/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:32:34 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:17 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	index;
	char	*str_casted;

	index = 0;
	str_casted = (char *)str;
	while (index < n)
	{
		if ((unsigned char)str_casted[index] == (unsigned char)c)
			return ((void *)&str_casted[index]);
		index++;
	}
	return (NULL);
}
