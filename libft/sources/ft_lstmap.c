/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:29:47 by zsyyida           #+#    #+#             */
/*   Updated: 2022/09/28 12:35:28 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	del(void *lst)
{
	free (lst);
}

// the storage is the content and is freed when we free the linked list
// (the stack of strings) pointing to it so no need to free it here.
// dont need to clear anything here bc clearing the stack of strings later
// when stack of ints is no longer pointing to it.
t_list	*ft_lstmap(t_list *lst, long long (*f)(t_list *), void (*del)(void *))
{
	t_list		*result;
	t_list		*curr;
	long long	*storage;

	(void)del;
	if (!lst)
		return (NULL);
	storage = ft_calloc (1, sizeof(long long));
	*storage = f(lst);
	result = ft_lstnew_ps(storage, 0);
	if (!result)
		return (0);
	curr = result;
	lst = lst->next;
	while (lst)
	{
		storage = ft_calloc (1, sizeof(long long));
		*storage = f(lst);
		ft_lstadd_back(&result, ft_lstnew_ps(storage, 0));
		curr = curr->next;
		lst = lst->next;
	}
	return (result);
}
