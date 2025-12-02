/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:36:36 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/02 09:16:24 by andriamr         ###   ########.fr       */
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

t_pars	*init_token(char *split_pipe)
{
	t_pars	*pars;
	t_pars	*tmp;
	
	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	pars->count_token = count_token(split_pipe);
	pars->all_token = split_token(split_pipe);
	if (!pars->all_token)
		return (NULL);
	pars->redir = init_dir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = pars->all_token[0];
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	if (!pars->arg)
		return (NULL);
	return (pars);
}

t_cmd	*cmd_init(char *line)
{
	t_cmd		*cmd;
	// t_global	*sav;
	// t_pars		**token
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
	while (cmd->sav->split_pipe[i])
	{
		cmd->all[i] = init_token(cmd->sav->split_pipe[i]);  
		i++;
	}
	cmd->all[i] = NULL;
	return (cmd);
}
