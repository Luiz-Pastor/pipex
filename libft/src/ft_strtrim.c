/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:02:07 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:25:10 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	app_character(const char ch, const char *set)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == ch)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*memory;
	size_t	index_start;
	size_t	index_end;
	size_t	index_memory;

	index_memory = 0;
	index_start = 0;
	index_end = ft_strlen(s1);
	while (s1[index_start] && app_character(s1[index_start], set))
		index_start++;
	while (index_end > index_start && app_character(s1[index_end - 1], set))
		index_end--;
	memory = (char *) malloc((index_end - index_start + 1) * sizeof(char));
	if (!memory)
		return (NULL);
	while (index_start < index_end)
	{
		memory[index_memory] = s1[index_start];
		index_memory++;
		index_start++;
	}
	memory[index_memory] = 0;
	return (memory);
}
