/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:25:18 by zsyyida           #+#    #+#             */
/*   Updated: 2023/03/23 10:33:14 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// printf("in lstnew %d\n", *(int *)new->content );
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (new == NULL)
		return (0);
	new -> content = content;
	new -> index = 0;
	new -> next = NULL;
	new -> prev = NULL;
	return (new);
}
