/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:54:13 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/24 16:59:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*pnew;

	if (!lst || !f)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new = f(lst);
	pnew = new;
	while (lst->next)
	{
		pnew->next = f(lst->next);
		pnew = pnew->next;
		lst = lst->next;
	}
	return (new);
}
