/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:29:11 by zsyyida           #+#    #+#             */
/*   Updated: 2022/01/26 15:28:58 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;
	unsigned int	i;

	i = 0;
	dst = (unsigned char *)b;
	c = (unsigned char)c;
	if (dst == NULL)
		return (0);
	while (i < len)
	{
		dst[i] = c;
		i++;
	}
	return (b);
}
