/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:48:03 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 20:53:55 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*cmd_init(char *line, char **envp, int last_exit_status)
{
	t_cmd	*cmd;

	cmd = alloc_cmd_base(envp, last_exit_status);
	if (!cmd)
		return (NULL);
	cmd->sav = global_init(line);
	if (!cmd->sav)
	{
		ft_free_split(cmd->env);
		free(cmd);
		return (NULL);
	}
	if (!line)
	{
		cmd->all = NULL;
		return (cmd);
	}
	build_token_list(cmd);
	return (cmd);
}

void	build_token_list(t_cmd *cmd)
{
	int		i;
	t_pars	*head;

	cmd->all = init_token1(cmd);
	if (!cmd->all)
	{
		if (cmd->sav)
		{
			if (cmd->sav->split_pipe)
				free_cmd2(cmd->sav->split_pipe);
			free(cmd->sav);
			cmd->sav = NULL;
		}
		return ;
	}
	head = cmd->all;
	i = 1;
	while (cmd->sav->split_pipe[i])
	{
		add_list_last(cmd->all, cmd->sav->split_pipe[i], cmd);
		i++;
	}
	cmd->all = head;
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
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

t_pars	*init_token1(t_cmd *cmd)
{
	t_pars	*pars;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	if (!init_pars_from_global(pars, cmd))
	{
		free_pars(pars);
		free(pars);
		return (NULL);
	}
	pars->next = NULL;
	return (pars);
}

t_pars	*init_token(char *split_pipe, t_cmd *cmd)
{
	t_pars	*pars;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	if (!init_pars_common(pars, split_pipe, cmd))
	{
		free_pars(pars);
		free(pars);
		return (NULL);
	}
	pars->next = NULL;
	return (pars);
}
