/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:07 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 17:46:53 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[34mruhan_zahra_shell\e[0m "

# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <limits.h>
# include <errno.h>

# include <sys/wait.h>
# include <sys/stat.h>
# include <strings.h>
# include <signal.h>

typedef struct s_elem
{
	int				type;
	char			*content;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

enum	e_rdr
{
	RDR_IN = 0,
	RDR_HEREDOC = 1,
	RDR_OUT_TRUNC = 2,
	RDR_OUT_APPEND = 3,
}	rdr;

typedef struct s_list_rdr
{
	char				*file;
	enum e_rdr			type;
	int					fd_in;
	int					fd_out;
	int					fd_pipe[2];
	struct s_list_rdr	*next;
	struct s_list_rdr	*prev;
}	t_list_rdr;

typedef struct s_list_cmd
{
	char				**cmd;
	char				*path;
	int					cmd_nbr;
	t_list_rdr			*rdr;
	struct s_list_cmd	*next;
	struct s_list_cmd	*prev;
}	t_list_cmd;

typedef struct s_shell
{
	char		**env;
	t_list_cmd	**cmd_list;
	int			size;
	int			*oper;
	int			**fd;
	int			nbr_pipes;
	int			*pid;
}	t_shell;

int	g_exit_status;

// RUHAN FUNCTIONS
int			is_sep(t_elem *elem);
char		*ft_null_strjoin(char *s1, char *s2);
char		*ft_free_strjoin(char *s1, char *s2);
int			is_in(char *str, char c);

t_elem		*create_elem(char *content, int len, int type, t_elem *prev);
void		free_next(t_elem *elem);
void		free_single(t_elem **head);
int			get_count(t_elem *elem, int c);

void		remove_quotes(t_elem *elem);
void		doubleq(t_shell *shell, t_elem *elem);
t_elem		*remove_nulls(t_elem *head);
void		join_words(t_elem *elem);
t_elem		*remove_spaces(t_elem *head);

char		*ft_getenv(t_shell *shell, char *var);
int			lenofenv(char *str);
void		sub_env(t_shell *shell, t_elem *elem);
void		handle_env(t_shell *shell, char **content, int start);

int			is_rdr(int type);
t_list_rdr	*make_rdr(char *str, int type, t_list_rdr *prev);
t_elem		*remove_rdr(t_elem *head);
t_list_rdr	*get_rdr(t_elem *elem, t_list_rdr *prev);

t_elem		*lex(char *line);
t_elem		*clean_elem(t_shell *shell, t_elem *head);
void		convert(t_shell *shell, t_elem *head);
void		parse_line(t_shell *shell, char *line);

int			syntax_error(t_elem *head, t_elem *elem);
void		nosuch_error(char *str, int exitcode, t_shell *shell, int flag);
void		error_exp(char *cmd, char *iden);
void		perm_error(int exit_code, t_shell *shell, int check);

void		free_elem(t_elem *head);
void		free_rdr(t_list_rdr *rdr);
void		free_cmd_list(t_list_cmd *cmd);
void		free_shell(t_shell *shell);
void		clean_shell(t_shell *shell);
// END OF RUHAN FUNCTIONS

void		rl_replace_line(const char *text, int clear_undo);
int			count_pipes(t_list_cmd *cmd);
void		ft_shlvl(t_shell *shell, int add);
t_shell		*init_shell(char **envp);

void		ft_builtins_child(t_shell *shell, t_list_cmd *cmd);
void		ft_builtins_parent(t_shell *shell, char **cmd);
int			check_builtins(char *cmd);

char		*ft_find_var(char *env);
int			does_exist(t_shell *shell, char *var);
int			check_valid(char *line);

void		ft_cd(t_shell *shell, char **cmd);
void		ft_echo(char **cmd);
void		ft_env(t_shell *shell);
void		ft_exit(t_shell *shell, char **cmd);
void		ft_export(t_shell *shell, char **cmd);
void		ft_pwd(void);
void		ft_unset(t_shell *shell, char **cmd);

char		*path(t_shell *shell, char *cmd);

void		execute(t_shell *shell, t_list_cmd *cmd_list);
void		ft_fork(t_shell *shell, t_list_cmd *cmd_list, int *pid);
void		exec_here_doc(t_list_rdr *rdr, t_shell *shell, int check);
void		exec_rdr(t_shell *shell, t_list_rdr *ptr, int check);
void		close_fds(t_shell *shell);

void		handle_nl(int sig);
void		handle_quit(int sig);
void		handle_prompt(int sig);
void		handle_sig_hd(int sig);

void		ft_free_2d(char **s);
void		ft_free_2d_int(int **s, int i);
char		**ft_cpy_2d(char **s);
void		sort_2d_array(char **s);
int			error(int *fd, t_shell *shell);

#endif
