/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:40:38 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:28 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_length;
	size_t	src_length;
	size_t	i;
	size_t	j;

	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = dest_length;
	j = 0;
	if (dstsize <= dest_length)
		return (src_length + dstsize);
	while ((j < (dstsize - dest_length - 1)) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_length + dest_length);
}
