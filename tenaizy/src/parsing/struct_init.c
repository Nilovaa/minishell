/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:36:36 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 20:51:27 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_arg_tools(t_arg_tools *tools, int count)
{
	tools->arg = ft_calloc(sizeof(char *), count + 1);
	tools->i = 0;
	tools->j = 0;
	tools->cmd_found = 0;
}

int	ft_process_arg(t_pars *token, t_arg_tools *tools)
{
	if (ft_is_redir(token->all_token[tools->i]))
	{
		tools->i++;
		if (token->all_token[tools->i])
			tools->i++;
	}
	else if (tools->cmd_found == 0)
	{
		tools->cmd_found = 1;
		tools->i++;
	}
	else
	{
		tools->arg[tools->j] = ft_strdup(token->all_token[tools->i]);
		if (!tools->arg[tools->j])
			return (0);
		tools->i++;
		tools->j++;
	}
	return (1);
}

char	**cpy_arg(t_pars *token)
{
	t_arg_tools	tools;

	if (!token->cmd)
		return (NULL);
	init_arg_tools(&tools, token->count_token);
	if (!tools.arg)
		return (NULL);
	while (token->all_token[tools.i])
	{
		if (!ft_process_arg(token, &tools))
		{
			ft_free_split(tools.arg);
			return (NULL);
		}
	}
	tools.arg[tools.j] = NULL;
	return (tools.arg);
}

t_cmd	*alloc_cmd_base(char **envp, int last_exit_status)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->env = cpy_env(envp);
	cmd->last_exit_status = last_exit_status;
	return (cmd);
}
