/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:48:18 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:38 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	index;
	char	*casted;

	index = 0;
	casted = (char *)str;
	while (index < n)
	{
		casted[index] = (unsigned char)c;
		index++;
	}
	return ((void *)casted);
}
