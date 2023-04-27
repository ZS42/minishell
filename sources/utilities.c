/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:29:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 17:16:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_list(t_list_cmd *cmd_list)
{
	t_list_cmd	*ptr;

	if (!cmd_list)
		return ;
	ptr = cmd_list;
	while (ptr != NULL)
	{
		ft_print2d(ptr->cmd);
		print_list_rdr(ptr->rdr);
		ptr = ptr->next;
	}
}

void	ft_free_2d(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

char	**ft_cpy_2d(char **s)
{
	int		len;
	char	**new;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	new = ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	len = -1;
	while (s[++len])
		new[len] = ft_strdup_ft(s[len]);
	new[len] = NULL;
	return (new);
}

char	**remove_from2d(char **s, int i)
{
	int		len;
	char	**new;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	if (i >= len || i < 0)
		return (ft_cpy_2d(s));
	new = ft_calloc(len, sizeof(char *));
	if (!new)
		return (NULL);
	len = -1;
	while (s[++len] && len < i)
		new[len] = ft_strdup_ft(s[len]);
	while (s[++len])
		new[len - 1] = ft_strdup_ft(s[len]);
	new[len - 1] = NULL;
	return (new);
}

void	ft_print2d(char **s)
{
	int		i;
	int		len;

	if (!s)
		return ;
	len = 0;
	i = 0;
	while (s[len])
		len++;
	while (i < len)
	{
		printf("%s\n", s[i]);
		i++;
	}
}
