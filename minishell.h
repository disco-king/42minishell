/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:04:47 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 15:04:47 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NAME "msh"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CHAR_PIPE '|'
# define CHAR_AMPERSAND '&'
# define CHAR_QUOTE '\''
# define CHAR_DOUBLE_QUOTE '\"'
# define CHAR_DOT_COMMA ';'
# define CHAR_TAB '\t'
# define CHAR_NEWLINE '\n'
# define CHAR_SPACE ' '
# define CHAR_INFILE '<'
# define CHAR_OUTFILE '>'
# define CHAR_SLASH '\\'

# define STR_PIPE "|"
# define STR_AMPERSAND "&"
# define STR_QUOTE "\'"
# define STR_DOUBLE_QUOTE "\""
# define STR_DOT_COMMA ";"
# define STR_TAB "\t"
# define STR_NEWLINE "\n"
# define STR_SPACE " "
# define STR_INFILE "<"
# define STR_OUTFILE ">"
# define STR_APPEND ">>"
# define EMPTY ""
# define HEREDOC "<<"
# define APPEND ">>"

# define IS_STRING 0
# define IS_TOKEN 1

typedef struct s_tmp{
	int		tmp;
	int		i;
	int		last_ret;
}	t_tmp;

typedef struct s_list{
	char			*tok;
	int				type;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_env{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_shell{
	t_list			*tokens;
	char			**awk;
	int				fdin;
	int				fdout;
	int				fderr;
	int				pipe;
	int				env_len;
	int				last_ret;
}	t_shell;

typedef struct s_pipe_list{
	char				**cmd;
	int					in_fd;
	int					out_fd;
	struct s_pipe_list	*next;
}	t_pipe_list;

int			final_exec(t_pipe_list *cmd, int read_fd);
int			pipe_to_next(t_pipe_list	*cmd, int read_fd);
t_pipe_list	*pipe_lstnew(char **content);
t_pipe_list	*free_lst(t_pipe_list *list);
char		*get_list(t_pipe_list *cmds);
void		add_pipe_list(t_pipe_list **start, char **str);
int			pipe_ret_error(int code, int in_fd, int out_fd);

int			exec(char **cmd, int infile, int outfile);
char		**free_all(char **ret);
int			get_cmd(char **argv);
char		**find_path(char **env);
char		*check_access(char *cmd, char **path);
char		*ft_strstr(const char *haystack, const char *needle);
char		**ft_split(char *str, char c);
int			close_exit(int code);
void		close_fds(int in_fd, int out_fd);
void		shell_init(t_shell *shell);
void		catch_signals(void);

void		add_list(t_list **start, char *str, int flag);
void		list_clear(t_list **lst);

void		print_tokens(t_list *lst);
int			get_arglen(t_list *lst);
void		print_args(char **arg);
void		print_error(char *cmd, char *error, char *arg);
int			all_digits(char *str);
int			ptr_count(char **arr);
int			builtins(t_pipe_list *cmd, t_shell *shell);
char		**new_env(t_shell *shell);

int			ft_export(const char *name, const char *value, t_shell *shell);
int			export_parse(char **args, t_shell *shell);
const char	*get_equals(const char *str);
int			ft_pwd(char **args);
int			ft_cd(char **path, t_shell *shell);
int			ft_exit(char *line, int len);
int			ft_env(char **args);
int			ft_unset(const char *name);
int			ft_echo(char **args);
int			ft_dist(int (*func)(), t_pipe_list *cmd);
int			check_builtin(char *cmd);
int			unset_cycle(char **arr);
int			get_shlvl(t_shell *shell);

char		**get_var_adress(const char *name);
int			check_empty(char *line);

void		print_ptoken(t_pipe_list *lst);
t_pipe_list	*trim_token(char **str, t_shell shell, t_list *tok);
void		free_pipe_list(t_pipe_list **lst);
int			pipeline(t_pipe_list *lst, t_shell *shell);
void		close_fds_pipeline(t_pipe_list *lst);

int			ft_infile(t_pipe_list *cmd, int last_ret);
int			ft_outfile(t_pipe_list *cmd);
char		**cut_redirect(char **cmd, char *redir);
int			pipeline_error(t_pipe_list *lst, char *try_cmd);
void		get_fds(t_pipe_list *cmd, int read_fd, int p_writer);
void		dup_io(t_pipe_list *cmd);

void		signals(void);
void		signals2(void);
void		interrupt(int num);
void		interrupt_cmd(int num);
int			exit_code(int code);
void		rl_replace_line(const char *text, int clear_undo);

char		*env_cnt(char *line, int *tmp, int last_ret);
char		*env_cnt_add(char *line, int m, int x);
void		add_env(char *line, char *str, t_tmp *data);

int			slash_handler(char *line, int *tmp);
int			get_word(int *i, char *line, t_shell *shell);
char		*get_word_add(char *line, int j, int tmp, int last_ret);

int			doubleq_handler(char *line, int *tmp, int *j, int last_ret);
int			quote_handler(char *line, int *tmp, int *j);
void		quote_handler_add(char *line, char *str, int *tmp, int *i);
void		doubleq_handler_add(char *line, char *str, t_tmp *data);

int			quote_error(void);
int			ft_dollar(char c);
int			is_token(char c);

char		**lst_to_char(t_list *lst);
int			get_infile(t_shell *shell, char *line, int *i);
int			get_outfile(t_shell *shell, char *line, int *i);
int			ft_parser(char *line, t_shell *shell);

void		env_cnt_mem(char *line, int *tmp, int *j, int last_ret);
void		env_cnt_mem_add(char *line, int m, int x, int *j);

int			heredoc_handler(char **cmd, char *del, int last_ret);
char		**cut_redirect(char **cmd, char *redir);
int			redirect_error(char *filename);
int			is_redirect(char c);
int			is_space(char c);

extern char	**environ;

#endif 