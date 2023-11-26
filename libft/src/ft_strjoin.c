/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:38:30 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:23 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*memory;
	size_t	index_memory;
	size_t	s1_length;
	size_t	s2_length;

	index_memory = 0;
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	memory = (char *) malloc(sizeof(char) * (s1_length + s2_length + 1));
	if (!memory)
		return (NULL);
	while (index_memory < s1_length || index_memory < s2_length)
	{
		if (index_memory < s1_length)
			memory[index_memory] = s1[index_memory];
		if (index_memory < s2_length)
			memory[index_memory + s1_length] = s2[index_memory];
		index_memory++;
	}
	memory[s1_length + s2_length] = '\0';
	return (memory);
}
