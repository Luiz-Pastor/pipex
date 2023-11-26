/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:51:44 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:25:15 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*memory;
	size_t	count;
	size_t	s_length;

	count = 0;
	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		return (ft_strdup(""));
	if (s_length < len)
		len = s_length;
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	memory = (char *) malloc((len + 1) * sizeof(char));
	if (!memory)
		return (NULL);
	while (count < len && s[start])
	{
		memory[count] = s[start];
		count++;
		start++;
	}
	memory[count] = '\0';
	return (memory);
}
