/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:36:19 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/04 14:02:32 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// added line 53 bc was missing last letter in minishell
static int	ft_cntwrd(char *s, char c)
{
	unsigned int	i;
	int				cnt_wrd;

	i = 0;
	if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		i++;
	cnt_wrd = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0')
			&& (!(s[i] == c || s[i] == '\0')))
		{
			cnt_wrd++;
		}
		i++;
	}
	return (cnt_wrd);
}

static int	ft_wrd_len(char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		s++;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*ft_strndup_ft( char *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free_str(char **s, int i)
{
	if (!s)
	{
		while (i-- != 0)
			free(s[i]);
		free(s);
	}
}

char	**ft_split(char *s, char c)
{
	int		wrd_len;
	int		wrd_cnt;
	int		i;
	char	**result;

	i = 0;
	if (!s)
		return (NULL);
	wrd_cnt = ft_cntwrd(s, c);
	result = (char **)malloc(sizeof(char *) * (wrd_cnt + 1));
	if (result == NULL)
		return (NULL);
	while (i < wrd_cnt)
	{
		while ((*s == c || *s == '\t') && *s)
			s++;
		wrd_len = ft_wrd_len(s, c);
		result[i] = ft_strndup_ft(s, wrd_len);
		if (!result[i])
			ft_free_str(result, wrd_cnt - 1);
		s = s + wrd_len;
		i++;
	}
	result[i] = NULL;
	return (result);
}
