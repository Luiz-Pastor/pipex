/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:08:10 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:08 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned long long	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == (unsigned char)c)
			return ((char *)&str[index]);
		index++;
	}
	if (!str[index] && !((char)c))
		return ((char *)&str[index]);
	return (NULL);
}
