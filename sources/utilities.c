/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:29:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		new[len] = ft_strdup(s[len]);
	new[len] = NULL;
	return (new);
}

// sorts according to ascii so lowercase comes after all uppercase
	// problem here 44. conflict with unset

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_2d_array(char **strs)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	while (strs[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = i;
		while (++j < len)
			if (ft_strcmp(strs[i], strs[j]) > 0)
				ft_swap(&strs[i], &strs[j]);
	}
}

int	error(int *fd, t_shell *shell)
{
	close (fd[0]);
	close (fd[1]);
	printf("ERROR: %s\n", strerror(errno));
	free(shell);
	exit (0);
}
