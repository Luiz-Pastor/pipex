/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 00:57:21 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:33 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		index;
	char		*dest_casted;
	const char	*src_casted;

	index = 0;
	dest_casted = (char *)dest;
	src_casted = (const char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest_casted > src_casted)
	{
		while (n-- > 0)
			dest_casted[n] = src_casted[n];
	}
	else
	{
		while (index < n)
		{
			dest_casted[index] = src_casted[index];
			index++;
		}
	}
	return ((void *)dest_casted);
}
