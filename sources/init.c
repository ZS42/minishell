/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:12:09 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 20:44:56 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_list_cmd *cmd)
{
	int	pipe;

	if (!cmd)
		return (0);
	pipe = 0;
	cmd = cmd->next;
	while (cmd && ++pipe)
		cmd = cmd->next;
	return (pipe);
}

void	ft_shlvl(t_shell *shell, int add)
{
	char	*value;
	int		lvl;
	int		i;

	i = -1;
	while (shell->env[++i])
	{
		if (strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			value = ft_getenv(shell, "SHLVL");
			lvl = ft_atoi(value) + add;
			free(value);
			value = ft_itoa(lvl);
			free (shell->env[i]);
			shell->env[i] = ft_strjoin("SHLVL=", value);
			free(value);
		}
	}
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (0);
	shell->env = ft_cpy_2d(envp);
	shell->cmd_list = NULL;
	shell->oper = NULL;
	shell->pid = NULL;
	shell->size = 0;
	shell->nbr_pipes = 0;
	return (shell);
}
