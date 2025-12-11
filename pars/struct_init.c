/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:36:36 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 13:24:19 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"

t_global	*global_init(char *line)
{
	t_global	*tmp;

	tmp = ft_calloc(sizeof(t_global), 1);
	if (!tmp)
		return (NULL);
	tmp->line = line;
	tmp->pipe = ft_count_pipe(line);
	tmp->split_pipe = split_pipe(line);
	if (!tmp->split_pipe)
		return (NULL);
	return (tmp);
}

t_dir	*init_dir(char **token)
{
	int 	i;
	t_dir	*redir;

	i = 0;
	redir = ft_calloc(sizeof(t_dir), 1);
	if (!redir)
		return (NULL);
	redir->dir_in = 0;
	redir->dir_out = 0;
	redir->dir_in2 = 0;
	redir->dir_out2 = 0;
	while (	token[i])
	{
		if (ft_strncmp(">", token[i], 2))
			redir->dir_in++;
		else if (ft_strncmp("<", token[i], 2))
			redir->dir_out++;
		else if (ft_strncmp("<<", token[i], 3))
			redir->dir_in2++;
		else if (ft_strncmp(">>", token[i], 3))
			redir->dir_out2++;
		i++;
	}
	return (redir);
}

char **cpy_arg(t_pars *token)
{
	char	**arg;
	int		i;

	i = 0;
	arg = ft_calloc(sizeof(char *), token->count_token);
	if (!arg)
		return (NULL);
	while (token->all_token[i + 1])
	{
		arg[i] = ft_strdup(token->all_token[i + 1]);
		if (!arg[i])
			return (NULL);
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

t_cmd	*cmd_init(char *line)
{
	t_cmd		*cmd;
	t_pars		*tmp;
	int			i;
	
	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->sav = global_init(line);
	if (!cmd->sav)
		return (NULL);
	cmd->all = ft_calloc(sizeof(t_pars), ft_count_pipe(line) + 1);
	if (!cmd->all)
		return (NULL);
	cmd->all = init_token(cmd->sav->split_pipe[i]);
	tmp = cmd->all;
	i++;
	while (cmd->sav->split_pipe[i])
	{
		add_list_last(cmd->all, cmd->sav->split_pipe[i]);  
		i++;
	}
	cmd->all = tmp;
	return (cmd);
}
