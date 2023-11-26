/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:33:12 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:51 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < (n - 1) && str1[index] == str2[index] \
	&& (str1[index] || str2[index]))
		index++;
	if (n != 0)
		return ((unsigned char)str1[index] - (unsigned char)str2[index]);
	return (0);
}
