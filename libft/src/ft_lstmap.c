/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:35:56 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:00 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*delete_content(void *content, void (*del)(void *))
{
	del(content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy_head;
	t_list	*cpy_aux;
	void	*aux;

	if (!lst || !f || !del)
		return (NULL);
	aux = f(lst->content);
	cpy_head = ft_lstnew(aux);
	if (!cpy_head)
		return (delete_content(aux, del));
	cpy_aux = cpy_head;
	while (lst->next)
	{
		lst = lst->next;
		aux = f(lst->content);
		cpy_aux->next = ft_lstnew(aux);
		if (!cpy_aux->next)
		{
			ft_lstclear(&cpy_head, del);
			return (delete_content(aux, del));
		}
		cpy_aux = cpy_aux->next;
	}
	return (cpy_head);
}
