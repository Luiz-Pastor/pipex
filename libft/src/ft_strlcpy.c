/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:12:09 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:35 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	index;

	index = 0;
	if (!dest || !src)
		return (NULL);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(src);
	if (size == 0)
		return (length);
	while (src[index] && index < (size - 1))
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (length);
}
