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

char	**cpy_arg(t_pars *token)
{
	char	**arg;
	int		i;
	int		j;
	int		cmd_status;

	j = 0;
	i = 0;
	cmd_status = 0;
	if (!token->cmd)
		return (NULL);
	arg = ft_calloc(sizeof(char *), token->count_token + 1);
	if (!arg)
		return (NULL);
	while (token->all_token[i])
	{
		if (ft_is_redir(token->all_token[i]))
		{
			i++;
			if (token->all_token[i])
				i++;
		}
		else if (cmd_status == 0)
		{
			cmd_status = 1;
			i++;
		}
		else
		{
			arg[j] = ft_strdup(token->all_token[i]);
			if (!arg[j])
				return (ft_free_split(arg), NULL);
			i++;
			j++;
		}
	}
	arg[j] = NULL;
	return (arg);
}

t_cmd	*cmd_init(char *line, char **envp, int last_exit_status)
{
	t_cmd		*cmd;
	t_pars		*tmp;
	int			i;

	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->env = cpy_env(envp);
	cmd->last_exit_status = last_exit_status;
	cmd->sav = global_init(line);
	if (!cmd->sav)
		return (NULL);
	if (!line)
	{
		cmd->all = NULL;
		return (cmd);
	}
	cmd->all = init_token1(cmd);
	tmp = cmd->all;
	i++;
	while (cmd->sav->split_pipe[i])
	{
		add_list_last(cmd->all, cmd->sav->split_pipe[i], cmd);
		i++;
	}
	cmd->all = tmp;
	return (cmd);
}

// void printf_test(t_cmd *cmd)
// {
// 	printf("debut test\n");
// 	printf("test global ==\n");
// 	printf("cmd->global->line = %s\n", cmd->sav->line);
// 	printf("cmd->global->pipe = %d\n", cmd->sav->pipe);
// 	printf("split-pipe\n");
// 	print_cmd(cmd->sav->split_pipe);
// 	printf("split-pipe\n");
// 	printf("\ntest pars\n");
// 	printf("cmd->pars->count_token = %d\n", cmd->all->count_token);
// 	print_token(cmd->all->all_token);
// 	printf("cmd->pars->cmd = %s\n", cmd->all->cmd);
// 	print_cmd(cmd->all->arg);
// }

char	**cpy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = ft_calloc(sizeof(char *), i + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}
