/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:04:57 by lpastor-          #+#    #+#             */
/*   Updated: 2023/12/01 08:50:12 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] && s2[index] && s1[index] == s2[index])
		index++;
	return (s1[index] - s2[index]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t	index;

	index = 0;
	while (s1[index] && s2[index] && s1[index] == s2[index] && count-- > 0)
		index++;
	return (s1[index] - s2[index]);
}