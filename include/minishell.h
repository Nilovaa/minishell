/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:57 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 22:05:09 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../LIBFT/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_expand
{
	char			*res;
	int				i;
	int				q[2];
}	t_expand;

typedef struct s_arg_tools
{
	char			**arg;
	int				i;
	int				j;
	int				cmd_found;
}	t_arg_tools;

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}	t_str;

typedef struct s_global
{
	char			*line;
	int				pipe;
	char			**split_pipe;
	int				exit;
}	t_global;

typedef struct s_dir
{
	char			**file_in;
	char			**file_out;
	char			**file_in2;
	char			**file_out2;
	char			**heredoc_files;
	t_global		global;
}	t_dir;

typedef struct s_pars
{
	int				count_token;
	char			**all_token;
	char			*cmd;
	char			**arg;
	int				return_value;
	t_dir			*redir;
	t_global		*global;
	struct s_pars	*next;
}	t_pars;

typedef struct s_cmd	t_cmd;

struct s_cmd
{
	t_pars			*all;
	t_global		*sav;
	char			**env;
	int				last_exit_status;
	t_cmd			*cmd_base;
};

typedef struct s_child_data
{
	t_pars	*pars;
	t_cmd	*cmd;
	int		**pipes;
	pid_t	*pids;
	int		index;
	int		nb_cmds;
}	t_child_data;

typedef struct s_fork_data
{
	t_pars	*pars;
	t_cmd	*cmd;
	int		**pipes;
	pid_t	*pids;
	int		nb_cmds;
}	t_fork_data;

int			len_sep(char *str);
int			ft_count_pipe(char *str);
t_pars		*parssing(char *str);
void		print_cmd(char **str);
void		print_token(char **str);
int			skip_2cot(char *str);
int			skip_1cot(char *str);
int			cat_1cot(char *src, char *dest, int i, int k);
int			cat_2cot(char *src, char *dest, int i, int k);
void		free_cmd2(char **dest);
void		free_redir(t_dir *redir);
void		free_pars(t_pars *pars);
void		free_all(t_cmd *cmd);
int			check_double_pipe(int i, char *str);
int			check_pipe(char *str);
char		*get_cmd_name(char **tokens);
void		init_arg_tools(t_arg_tools *tools, int count);
char		*add_cmd(char **all_token);
t_cmd		*alloc_cmd_base(char **envp, int last_exit_status);
void		build_token_list(t_cmd *cmd);
int			init_pars_from_global(t_pars *pars, t_cmd *cmd);
int			init_pars_common(t_pars *pars, char *split_pipe, t_cmd *cmd);
void		add_list_last(t_pars *pars, char *split_pipe, t_cmd *cmd);
t_pars		*init_token1(t_cmd *cmd);
t_pars		*init_token(char *split_pipe, t_cmd *cmd);
t_dir		*init_redir(char **all_token);
char		**join_redir(char *file, char **redir);
char		**split_pipe(char *str);
t_global	*global_init(char *line);
t_dir		*init_dir(char **token);
char		**cpy_arg(t_pars *token);
t_cmd		*cmd_init(char *line, char **env, int last_exit_status);
char		**cpy_env(char **envp);
char		*get_env_val(char *key, t_cmd *cmd);
int			handle_var(char *str, int i, char **res, t_cmd *cmd);
char		*expand_and_clean(char *str, t_cmd *cmd);
void		process_all_tokens(t_pars *pars, t_cmd *cmd);
int			ft_is_space(char c);
int			ft_atoll(char *str, int sign);
int			skip_space(char *str);
int			check_qote(char *str);
char		**split_token_utils(char *str, char **dest);
char		**split_token(char *str);
int			count_token(char *str);
int			len_token(char *str);
void		update_quote_state(char c, int *in_sq, int *in_dq);
int			ft_is_redir(char *str);
char		*cpy_token(char *str, char *dest);
void		print_all(t_cmd *cmd);
void		print_cdm2(char **str);
void		print_redir(t_dir *redir);
void		ft_syntax_error(void);
void		print_cmd(char **str);
void		print_token(char **str);
void		parsing(void);
t_str		*init_str(char *str);
t_str		*add_str_last(t_str *list, char *str);
t_str		*char_to_list(char **str);
int			ft_list_size_str(t_str *list);
char		**list_to_char(t_str *list);
void		ft_exec_simple(t_pars *pars, t_cmd *cmd);
char		*ft_make_path(t_pars *pars, t_cmd *cmd);
char		**ft_make_args(t_pars *pars);
int			ft_echo(t_pars *pars);
int			ft_cd(t_pars *pars, t_cmd *cmd);
int			ft_pwd(t_pars *pars);
int			ft_exit(t_pars *pars, t_cmd *cmd);
int			ft_export(t_pars *pars, t_cmd *cmd);
int			ft_unset(t_pars *pars, t_cmd *cmd);
int			ft_env(t_pars *pars, t_cmd *cmd);
int			ft_is_only_spaces(char *str);
void		ft_print_exit_code(t_pars *pars);
void		ft_first_child(t_pars *pars, t_cmd *cmd, int fd[2]);
void		ft_second_child(t_pars *pars, t_cmd *cmd, int fd[2]);
void		ft_exec_simple_pipe(t_pars *pars, t_cmd *cmd);
int			ft_is_builtin(char *cmd);
int			ft_exec_builtin_only(t_pars *pars, t_cmd *cmd);
void		ft_check_builtins(t_pars *pars, t_cmd *cmd);
void		ft_exec_pipeline(t_pars *pars, t_cmd *cmd);
int			ft_wait_all(pid_t *pids, int nb_cmds);
void		ft_setup_redirections(t_child_data *data);
int			**ft_create_pipes(int nb_pipes);
void		ft_free_pipes(int **pipes, int nb_pipes);
void		ft_close_all_pipes(int **pipes, int nb_pipes);
int			ft_count_cmds(t_pars *pars);
int			ft_redirection(t_dir *redir, t_cmd *cmd, int is_child);
int			ft_process_heredocs(t_dir *redir);
void		ft_cleanup_heredocs(t_dir *redir);
void		ft_signal_interactive(void);
void		ft_signal_child(void);
void		ft_signal_heredoc(void);
void		ft_signal_ignore(void);
int			ft_get_signal_received(void);
void		ft_reset_signal_received(void);
int			ft_change_to_dir(char *path, t_pars *pars, t_cmd *cmd);
void		ft_update_pwd(t_cmd *cmd);
void		ft_update_oldpwd(t_cmd *cmd, char *oldpwd);
void		ft_exec_simple(t_pars *pars, t_cmd *cmd);
int			ft_change_to_dir(char *path, t_pars *pars, t_cmd *cmd);
void		ft_exec_child_command(t_pars *pars, t_cmd *cmd);
void		ft_execute_pipe(t_pars *pars, t_cmd *cmd, int fd[2]);
char		*ft_get_path(t_pars *pars, t_cmd *cmd);
char		**ft_get_argv(t_pars *pars, char *path);
int			ft_handle_heredoc(t_pars *pars, char *path, char **argv);
pid_t		ft_exec(char *path, char **argv, t_pars *pars, t_cmd *cmd);
void		ft_parent_wait(pid_t pid, t_pars *pars, char *path, char **argv);
void		ft_handle_sigint(int sig);
void		ft_handle_sigint_heredoc(int sig);
void		ft_child_process(t_child_data *data);
void		ft_cleanup_all_heredocs(t_pars *pars);
pid_t		*ft_fork_processes(t_fork_data *data);
char		*ft_build_heredoc_name(char *pid_str, char *num);
int			ft_read_file(char *delim, int fd);
char		*ft_tmp_heredoc(void);
int			ft_create_heredoc(char *delim, char *tmp_file);
int			ft_process_heredocs(t_dir *redir);
void		ft_cleanup_heredocs(t_dir *redir);
t_cmd		*ft_init_cmd_base(char **env);
void		ft_update_signal_status(t_cmd *cmd_base);

#endif