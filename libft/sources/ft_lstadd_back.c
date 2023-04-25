/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:59:44 by zsyyida           #+#    #+#             */
/*   Updated: 2023/03/23 10:17:44 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (new == NULL)
		return (*lst);
	ptr = *lst;
	if (!ptr)
		ptr = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	return (*lst);
}
