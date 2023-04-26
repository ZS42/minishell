/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:07 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 18:31:07 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[34mruhan_zahra_shell\e[0m "

# include "../libft/include/libft.h"
// for printf
# include <stdio.h>
// for PATH_MAX
# include <limits.h>
// for malloc
# include <stdlib.h>
// for prompt
# include <readline/readline.h>
// for history
# include <readline/history.h>
// for read , write
# include <unistd.h>
// for open, close
# include <fcntl.h>
// for error
# include <errno.h>
// for wait amd waitpid
# include <sys/wait.h>
# include <sys/stat.h>
// for stderror
# include <errno.h>
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
}rdr;

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
int			ft_isalnum(int c);
int			is_sep(t_elem *elem);
char		*ft_null_strjoin(char *s1, char *s2);
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
void		nosuch_error(char *str, int exitcode, t_shell *shell);
void		nosuch_error1(char *str, int exitcode);
void		perm_error(int exit_code, t_shell *shell);

void		free_elem(t_elem *head);
void		free_rdr(t_list_rdr *rdr);
void		free_cmd_list(t_list_cmd *cmd);
void		free_shell(t_shell *shell);
void		clean_shell(t_shell *shell);
// END OF RUHAN FUNCTIONS

t_shell		*init_shell(char **envp);
void		ft_shlvl(t_shell *shell, int add);
t_list_cmd	**init_cmd_list(t_elem	*head, t_shell *shell, char *s);
int			count_pipes(t_list_cmd *cmd);

void		ft_builtins_child(t_shell *shell, t_list_cmd *cmd_list);
void		ft_builtins_parent(t_shell *shell, t_list_cmd *cmd_list);
int			check_builtins(char *cmd);

void		ft_exit(t_shell *shell, t_list_cmd *l);

void		ft_cd(t_shell *shell, char **cmd);

void		ft_env(t_shell *shell);
char		*ft_getenv(t_shell *shell, char *var);
void		ft_change_env(t_shell *shell, char *var, char *str);

void		ft_echo(char **cmd);

void		ft_pwd(void);

char		*ft_find_var(char *env);
void		ft_print_export(t_shell *shell);

int			does_exist(t_shell *shell, char *var);
void		ft_export(t_shell *shell, char **cmd);

int			check_valid(char *line);
void		ft_unset(t_shell *shell, char **cmd);

char		*path(t_shell *shell, char *cmd);

char		*ft_here_doc(t_shell *shell, char *delimiter, char *here_doc);
char		*ft_expand_here_doc(t_shell *shell, char array[999998]);

void		execute(t_shell *shell, t_list_cmd *cmd_list);
int			**open_pipes(t_shell *shell);
void		ft_fork(t_shell *shell, t_list_cmd *cmd_list, int *pid);
void		ft_dupe_pipes(t_shell *shell, int i);
void		child_process(t_shell *shell, t_list_cmd *cmd_list);
void		exec_rdr(t_shell *shell, t_list_rdr *ptr);
void		exec_rdr1(t_shell *shell, t_list_cmd *cmd_list);
void		exec_in(t_list_rdr *rdr, t_shell *shell);
void		exec_out(t_list_rdr *rdr, t_shell *shell);
void		exec_here_doc(t_list_rdr *rdr, t_shell *shell);
void		error_pipe(char **cmd, t_shell *shell);
void		close_fds(t_shell *shell);
void		ft_wait(int *pid, int nbr_pipes);

void		print_list(t_list_cmd *cmd_list);
void		ft_print2d(char **s);
void		print_list_rdr(t_list_rdr *rdr_head);
void		print_cmd(t_list_cmd *head);

void		handle_sig_child(int sig);
void		handle_sig(int sig);

void		ft_free_2d(char **s);
void		ft_free_2d_int(int **s, int i);
char		**ft_cpy_2d(char **s);
char		**remove_from2d(char **cmd, int i);
void		sort_2d_array(char **s);
int			error(int *fd, t_shell *shell);
int			ft_putnbr(int n);

#endif
