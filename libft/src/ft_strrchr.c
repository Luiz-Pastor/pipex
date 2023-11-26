/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:47:11 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:25:04 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	long long	index;

	index = ft_strlen(str) - 1;
	if (!str[index + 1] && !((char)c))
		return ((char *)&str[index + 1]);
	while (index >= 0)
	{
		if (str[index] == (unsigned char)c)
			return ((char *)&str[index]);
		index--;
	}
	return (NULL);
}
