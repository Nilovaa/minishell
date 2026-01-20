/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:36:36 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/16 16:23:53 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_arg_tools(t_arg_tools *tools, int count)
{
	tools->arg = ft_calloc(sizeof(char *), count + 1);
	tools->i = 0;
	tools->j = 0;
	tools->cmd_found = 0;
}

static int	ft_process_arg(t_pars *token, t_arg_tools *tools)
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

// char	**cpy_arg(t_pars *token)
// {
// 	char	**arg;
// 	int		i;
// 	int		j;
// 	int		cmd_status;

// 	j = 0;
// 	i = 0;
// 	cmd_status = 0;
// 	if (!token->cmd)
// 		return (NULL);
// 	arg = ft_calloc(sizeof(char *), token->count_token + 1);
// 	if (!arg)
// 		return (NULL);
// 	while (token->all_token[i])
// 	{
// 		if (ft_is_redir(token->all_token[i]))
// 		{
// 			i++;
// 			if (token->all_token[i])
// 				i++;
// 		}
// 		else if (cmd_status == 0)
// 		{
// 			cmd_status = 1;
// 			i++;
// 		}
// 		else
// 		{
// 			arg[j] = ft_strdup(token->all_token[i]);
// 			if (!arg[j])
// 				return (ft_free_split(arg), NULL);
// 			i++;
// 			j++;
// 		}
// 	}
// 	arg[j] = NULL;
// 	return (arg);
// }

// t_cmd	*cmd_init(char *line, char **envp, int last_exit_status)
// {
// 	t_cmd		*cmd;
// 	t_pars		*tmp;
// 	int			i;

// 	i = 0;
// 	cmd = ft_calloc(sizeof(t_cmd), 1);
// 	if (!cmd)
// 		return (NULL);
// 	cmd->env = cpy_env(envp);
// 	cmd->last_exit_status = last_exit_status;
// 	cmd->sav = global_init(line);
// 	if (!cmd->sav)
// 		return (NULL);
// 	if (!line)
// 	{
// 		cmd->all = NULL;
// 		return (cmd);
// 	}
// 	cmd->all = init_token1(cmd);
// 	tmp = cmd->all;
// 	i++;
// 	while (cmd->sav->split_pipe[i])
// 	{
// 		add_list_last(cmd->all, cmd->sav->split_pipe[i], cmd);
// 		i++;
// 	}
// 	cmd->all = tmp;
// 	return (cmd);
// }

static t_cmd	*alloc_cmd_base(char **envp, int last_exit_status)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->env = cpy_env(envp);
	cmd->last_exit_status = last_exit_status;
	return (cmd);
}

static void	build_token_list(t_cmd *cmd)
{
	int		i;
	t_pars	*head;

	cmd->all = init_token1(cmd);
	if (!cmd->all)
		return ;
	head = cmd->all;
	i = 1;
	while (cmd->sav->split_pipe[i])
	{
		add_list_last(cmd->all, cmd->sav->split_pipe[i], cmd);
		i++;
	}
	cmd->all = head;
}

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
