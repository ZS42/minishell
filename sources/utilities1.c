/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:31:38 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 17:20:19 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
