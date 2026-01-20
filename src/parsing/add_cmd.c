/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 07:03:45 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/20 16:44:45 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_cmd(char **all_token)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (!all_token)
		return (NULL);
	while (all_token[i])
	{
		if (ft_strncmp(all_token[i], ">", 1) == 0
			|| ft_strncmp(all_token[i], "<", 1) == 0)
		{
			i++;
			if (all_token[i])
				i++;
		}
		else
			return (ft_strdup(all_token[i]));
	}
	return (cmd);
}

char	*get_cmd_name(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 1) == 0
			|| ft_strncmp(tokens[i], "<", 1) == 0)
		{
			if (tokens[i + 1])
				i += 2;
			else
				i++;
		}
		else
			return (tokens[i]);
	}
	return (NULL);
}

t_pars	*init_token(char *split_pipe, t_cmd *cmd)
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
	process_all_tokens(pars, cmd);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = add_cmd(pars->all_token);
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	if (!pars->arg)
		return (NULL);
	pars->next = NULL;
	return (pars);
}

t_pars	*init_token1(t_cmd *cmd)
{
	t_pars	*pars;
	t_pars	*tmp;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	pars->count_token = count_token(cmd->sav->split_pipe[0]);
	pars->global = cmd->sav;
	pars->all_token = split_token(cmd->sav->split_pipe[0]);
	if (!pars->all_token)
		return (NULL);
	process_all_tokens(pars, cmd);
	if (pars->all_token[0] && ft_is_redir(pars->all_token[0])
		&& (!pars->all_token[1] || ft_is_redir(pars->all_token[1])))
		return (ft_syntax_error(), NULL);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = add_cmd(pars->all_token);
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	if (!pars->arg)
		return (NULL);
	pars->next = NULL;
	return (pars);
}
