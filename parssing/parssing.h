/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:57 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/24 14:16:00 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_dir
{
	int		*dir_in;
	char	**file_in;
	int		*dir_out;
	char	**file_out;
	int		*dir_in2;
	char	**file_in2;
	int		*dir_out2;
	char	**file_out2;
}	t_dir;

typedef struct s_pars
{
	int		id;
	char	*cmd;
	char	**arg;
	t_dir	*redir;
}	t_pars;

typedef struct s_cmd
{
	int				nb_cmd;
	t_pars			all;
	struct s_cmd	*next;
}	t_cmd;

int		ft_count_pipe(char *str);
int		skip_2cot(char *str);
int		skip_1cot(char *str);
char	**split_pipe(char *str);
int		ft_count_pipe(char *str);
int		len_sep(char *str);
void	free_cmd2(char **dest);
void	ft_exit(void);
int		cat_1cot(char *src, char *dest, int i, int k);
int		cat_2cot(char *src, char *dest, int i, int k);
int ft_is_space(char c);
int skip_space(char *str);
int count_token(char *str);
char **split_token_utils(char *str, char **dest);
int len_token(char *str);
char *cpy_token(char *str, char *dest);
char **split_token(char *str);


t_pars	*parssing(char *str);
