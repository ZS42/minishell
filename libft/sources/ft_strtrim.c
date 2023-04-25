/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:09:41 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/10 13:57:30 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen_ft(s1);
	while (s1[start] && ft_strchr_ft(set, s1[start]))
		start++;
	while (end > start && s1[end - 1] && ft_strrchr(set, s1[end - 1]))
		end--;
	new_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &s1[start], end - start + 1);
	return (new_str);
}
