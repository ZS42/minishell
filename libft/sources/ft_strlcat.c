/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:49:32 by zsyyida           #+#    #+#             */
/*   Updated: 2022/12/05 15:25:18 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	int		i;

	i = 0;
	d_len = ft_strlen_ft(dst);
	s_len = ft_strlen_ft(src);
	if (d_len >= dstsize)
		return (dstsize + s_len);
	while (src[i] && ((d_len + i) < (dstsize - 1)))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
