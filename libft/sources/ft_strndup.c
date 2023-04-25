/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:59:34 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/20 14:02:17 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *s1, int len)
{
	char	*str;

	if (!s1 || !len)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}
