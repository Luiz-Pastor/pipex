/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:42:43 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:56:03 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		index;
	const char	*src_casted;
	char		*dest_casted;

	index = 0;
	if (!dest && !src)
		return (NULL);
	src_casted = (const char *)src;
	dest_casted = (char *)dest;
	while (index < n)
	{
		dest_casted[index] = src_casted[index];
		index++;
	}
	return ((void *)dest_casted);
}
