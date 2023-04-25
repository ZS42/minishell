/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:50:07 by zsyyida           #+#    #+#             */
/*   Updated: 2022/12/05 15:16:38 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_ft(void *dst, const void *src, size_t n)
{
	char			*d;
	char			*s;
	size_t			i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d == NULL && s == NULL)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
