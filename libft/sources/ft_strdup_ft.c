/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:33:15 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/20 14:01:14 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup_ft(const char *s1)
{
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	str = (char *)s1;
	len = ft_strlen_ft(s1);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_memcpy_ft(str, s1, len);
	str[len] = '\0';
	return (str);
}
