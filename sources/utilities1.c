/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:31:38 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 17:59:41 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// sorts according to ascii so lowercase comes after all uppercase
	// problem here 44. conflict with unset

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

void	print_list_rdr(t_list_rdr *r)
{
	write(1, "REACH\n", 6);
	if (!r)
		return ;
	while (r)
	{
		printf("type %d\n file %s\n", r->type, r->file);
		r = r->next;
	}
}
