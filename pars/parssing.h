/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:57 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 12:37:45 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_global
{
	char	*line;
	int		pipe;
	char	**split_pipe;
}	t_global;

typedef struct s_dir
{
	int		dir_in;
	char	**file_in;
	int		dir_out;
	char	**file_out;
	int		dir_in2;
	char	**file_in2;
	int		dir_out2;
	char	**file_out2;
}	t_dir;

typedef struct s_pars
{
	int				count_token;
	char			**all_token;
	char			*cmd;
	char			**arg;
	t_dir			*redir;
	struct s_pars	*next;
}	t_pars;

typedef struct s_cmd
{
	t_pars			*all;
	t_global		*sav;
}	t_cmd;

int			ft_count_pipe(char *str);
int			skip_2cot(char *str);
int			skip_1cot(char *str);
char		**split_pipe(char *str);
int			len_sep(char *str);
void		free_cmd2(char **dest);
void		ft_exit(void);
int			cat_1cot(char *src, char *dest, int i, int k);
int			cat_2cot(char *src, char *dest, int i, int k);
int			ft_is_space(char c);
int			skip_space(char *str);
int			count_token(char *str);
char		**split_token_utils(char *str, char **dest);
int			len_token(char *str);
char		*cpy_token(char *str, char *dest);
char		**split_token(char *str);
int			check_qote(char *str);
t_global	*global_init(char *line);
t_dir		*init_dir(char **token);
char		**cpy_arg(t_pars *token);
t_pars		*init_token(char *split_pipe);
t_cmd		*cmd_init(char *line);
int			check_pipe(char *str);
void		free_all(t_cmd *cmd);
void		add_list_last(t_pars *pars, char *split_pipe);
t_pars		*parssing(char *str);
