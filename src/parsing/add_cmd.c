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

static int	init_pars_common(t_pars *pars, char *split_pipe, t_cmd *cmd)
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

static int	init_pars_from_global(t_pars *pars, t_cmd *cmd)
{
	pars->count_token = count_token(cmd->sav->split_pipe[0]);
	pars->global = cmd->sav;
	pars->all_token = split_token(cmd->sav->split_pipe[0]);
	if (!pars->all_token)
		return (0);
	process_all_tokens(pars, cmd);
	if (pars->all_token[0] && ft_is_redir(pars->all_token[0])
		&& (!pars->all_token[1] || ft_is_redir(pars->all_token[1])))
		return (ft_syntax_error(), 0);
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

t_pars	*init_token(char *split_pipe, t_cmd *cmd)
{
	t_pars	*pars;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	if (!init_pars_common(pars, split_pipe, cmd))
	{
		free(pars);
		return (NULL);
	}
	pars->next = NULL;
	return (pars);
}

t_pars	*init_token1(t_cmd *cmd)
{
	t_pars	*pars;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	if (!init_pars_from_global(pars, cmd))
	{
		free(pars);
		return (NULL);
	}
	pars->next = NULL;
	return (pars);
}

t_global	*global_init(char *line)
{
	t_global	*tmp;

	tmp = ft_calloc(sizeof(t_global), 1);
	if (!tmp)
		return (NULL);
	if (!line)
	{
		tmp->line = NULL;
		tmp->exit = 0;
		tmp->pipe = 0;
		tmp->split_pipe = NULL;
		return (tmp);
	}
	tmp->line = line;
	tmp->exit = 0;
	tmp->pipe = ft_count_pipe(line);
	tmp->split_pipe = split_pipe(line);
	if (!tmp->split_pipe)
		return (NULL);
	return (tmp);
}
