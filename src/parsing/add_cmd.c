/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 07:03:45 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 04:16:30 by andriamr         ###   ########.fr       */
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

int	init_pars_common(t_pars *pars, char *split_pipe, t_cmd *cmd)
{
	pars->count_token = count_token(split_pipe);
	pars->all_token = split_token(split_pipe);
	if (!pars->all_token)
		return (0);
	process_all_tokens(pars, cmd);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (0);
	pars->cmd = add_cmd(pars->all_token);
	if (pars->cmd)
	{
		pars->arg = cpy_arg(pars);
		if (!pars->arg)
			return (0);
	}
	else
		pars->arg = NULL;
	return (1);
}

static void	init_pars_global(t_pars *pars, t_cmd *cmd)
{
	pars->count_token = count_token(cmd->sav->split_pipe[0]);
	pars->global = cmd->sav;
	pars->all_token = split_token(cmd->sav->split_pipe[0]);
}

static int	ft_token_is_sp(t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->all_token[i])
	{
		if (ft_strncmp("&", pars->all_token[i], 1) == 0)
			return (ft_syntax_error(), 0);
		i++;
	}
	return (i);
}

int	init_pars_from_global(t_pars *pars, t_cmd *cmd)
{
	init_pars_global(pars, cmd);
	if (!pars->all_token)
		return (0);
	process_all_tokens(pars, cmd);
	if (pars->all_token[0] && ft_is_redir(pars->all_token[0])
		&& (!pars->all_token[1] || ft_is_redir(pars->all_token[1])))
		return (ft_syntax_error(), 0);
	if (!ft_token_is_sp(pars))
		return (0);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (0);
	pars->cmd = add_cmd(pars->all_token);
	if (pars->cmd)
	{
		pars->arg = cpy_arg(pars);
		if (!pars->arg)
			return (0);
	}
	else
		pars->arg = NULL;
	return (1);
}
