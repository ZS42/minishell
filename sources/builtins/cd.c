/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:04 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/28 20:59:52 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_error(char *file)
{
	ft_putstr_fd("ruhan_zahra_shell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = 1;
}

void	ft_change_env(t_shell *shell, char *var, char *value)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var, len)
			&& (!shell->env[i][len] || shell->env[i][len] == '='))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(var, value);
		}
		i++;
	}
}

void	call_old(t_shell *shell)
{
	char	*str;

	str = ft_getenv(shell, "OLDPWD");
	if (!str)
	{
		ft_putstr_fd("ruhan_zahra_shell: cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
	}
	else
		chdir(str);
	free(str);
}

void	call_tilde(t_shell *shell, char *cmd)
{
	char	*str;
	char	*join;

	str = ft_getenv(shell, "HOME");
	ft_putstr_fd("ruhan_zahra_shell: cd: HOME not set\n", 2);
	join = ft_strjoin(str, &cmd[1]);
	free(str);
	if (chdir(join) != 0)
		cd_error(join);
	free(join);
}

void	ft_cd(t_shell *shell, char **cmd)
{
	char	buff[PATH_MAX];
	char	*temp;

	g_exit_status = 0;
	getcwd(buff, PATH_MAX);
	if (!cmd[1])
	{
		temp = ft_getenv(shell, "HOME");
		chdir(temp);
		free(temp);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		call_old(shell);
	else if (cmd[1][0] == '~')
		call_tilde(shell, cmd[1]);
	else
		if (chdir(cmd[1]) != 0)
			cd_error(cmd[1]);
	ft_change_env(shell, "OLDPWD=", buff);
	getcwd(buff, PATH_MAX);
	ft_change_env(shell, "PWD=", buff);
}
