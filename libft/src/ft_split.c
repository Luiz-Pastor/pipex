/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:27:56 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:24:04 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strncpy(char *s1, char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && s2[index])
	{
		s1[index] = s2[index];
		index++;
	}
	s1[index] = '\0';
	return (s1);
}

static	char	**free_matrix(char **memory, size_t max)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		free(memory[i]);
		i++;
	}
	free(memory);
	return (NULL);
}

static char	**refill_matrix(char **memory, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			memory[k] = (char *) malloc((i - j + 1) * sizeof(char));
			if (!memory[k])
				return (free_matrix(memory, k));
			ft_strncpy(memory[k++], (char *)&s[j], i - j);
		}
	}
	memory[k] = NULL;
	return (memory);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**memory;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	memory = (char **) malloc((count + 1) * sizeof(char *));
	if (!memory)
		return (NULL);
	return (refill_matrix(memory, s, c));
}

void	*free_split(char **spl)
{
	int	index;

	index = 0;
	if (!spl)
		return (NULL);
	while (spl[index])
		free(spl[index++]);
	free(spl);
	return (NULL);
}
