/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:57 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/28 22:29:27 by nyrakoto         ###   ########.fr       */
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

typedef struct s_global
{
	char	*line;
	int		pipe;
	char	**split_pipe;
	int		exit;
}	t_global;

typedef struct s_dir
{
	char		**file_in;
	char		**file_out;
	char		**file_in2;
	char		**file_out2;
	t_global	global;
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

typedef struct s_cmd
{
	t_pars			*all;
	t_global		*sav;
}	t_cmd;
// split_utils
int			len_sep(char *str);
int			ft_count_pipe(char *str);
// 	main
t_pars		*parssing(char *str);
void		print_cmd(char **str);
void		print_token(char **str);
// 	ft_quote
int			skip_2cot(char *str);
int			skip_1cot(char *str);
int			cat_1cot(char *src, char *dest, int i, int k);
int			cat_2cot(char *src, char *dest, int i, int k);
// 	ft_exit
void		free_cmd2(char **dest);
void		free_redir(t_dir *redir);
void		free_pars(t_pars *pars);
void		free_all(t_cmd *cmd);
// 	checker_pipe
int			check_double_pipe(int i, char *str);
int			check_pipe(char *str);
char *get_cmd_name(char **tokens);
char *add_cmd(char **all_token);
// list_pars
void		add_list_last(t_pars *pars, char *split_pipe);
t_pars		*init_token1(t_cmd *cmd);
t_pars		*init_token(char *split_pipe);
t_dir		*init_redir(char **all_token);
char		**join_redir(char *file, char **redir);
//  split_by_pipie
char		**split_pipe(char *str);
// struct_init
t_global	*global_init(char *line);
t_dir		*init_dir(char **token);
char		**cpy_arg(t_pars *token);
t_cmd		*cmd_init(char *line);
// tokenisation
int			ft_is_space(char c);
int			skip_space(char *str);
int			check_qote(char *str);
// split_token
char		**split_token_utils(char *str, char **dest);
char		**split_token(char *str);
int			count_token(char *str);
int			len_token(char *str);
char		*cpy_token(char *str, char *dest);
// put_cmd
void		print_all(t_cmd *cmd);
void		print_cdm2(char **str);
void		print_redir(t_dir *redir);
//	pars_utils
void		print_cmd(char **str);
void		print_token(char **str);
void		parsing(void);

//	cmd_line
char *ft_make_path(t_pars *pars, char **envp);
char	**ft_make_args(t_pars *pars);

//	execution
void	ft_exec_simple(t_pars *pars, char **envp);
char 	*ft_make_path(t_pars *pars, char **envp);
char	**ft_make_args(t_pars *pars);

// builtins
int		ft_echo(t_pars *pars);
int		ft_cd(t_pars *pars);
int		ft_pwd(t_pars *pars);
int		ft_exit(t_pars *pars);
int		ft_export(t_pars *pars, char ***env);
int		ft_unset(t_pars *pars, char ***env);
int		ft_env(t_pars *pars, char **env);

#endif
