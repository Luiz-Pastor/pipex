/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:07:45 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:21:54 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char				*memory;
	size_t				index;
	unsigned long long	max;

	max = nitems * size;
	if (max > 4294967295)
		return (NULL);
	index = 0;
	memory = (char *)malloc(nitems * size);
	if (!memory)
		return (NULL);
	while (index < (nitems * size))
	{
		memory[index] = 0;
		index++;
	}
	return ((void *)memory);
}
