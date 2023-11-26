/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:20 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:22:42 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*aux;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		aux = current;
		current = current->next;
		if (del)
			del(aux->content);
		free(aux);
	}
	*lst = NULL;
}
