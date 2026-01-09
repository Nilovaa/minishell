/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:36:36 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/09 11:43:02 by andriamr         ###   ########.fr       */
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
	
	j = 0;
	i = 0;
	arg = ft_calloc(sizeof(char *), token->count_token);
	if (!arg)
		return (NULL);
	while (token->all_token[i])
	{
		if (ft_strncmp(token->all_token[i],token->cmd, ft_strlen(token->cmd) - 1) == 0)
			break;
		i++;
	}
	i++;	
	while (token->all_token[i])
	{
		if (ft_strncmp(token->all_token[i], ">", 1) == 0 || ft_strncmp(token->all_token[i], "<", 1) == 0)
			break;
		arg[j] = ft_strdup(token->all_token[i]);
		if (!arg[j])
			return (NULL);
		i++;
		j++;
	}
	arg[j] = NULL;
	return (arg);
}

t_cmd	*cmd_init(char *line)
{
	t_cmd		*cmd;
	t_pars		*tmp;
	int			i;

	i = 0;
	// cmd->env = cpy_env(envp);
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	// printf("global init\n");
	cmd->sav = global_init(line);
	if (!cmd->sav)
		return (NULL);
	if (!line)
	{
		cmd->all = NULL;
		return (cmd);
	}
	cmd->all = ft_calloc(sizeof(t_pars), ft_count_pipe(line) + 1);
	if (!cmd->all)
		return (NULL);
	// printf("init token\n");
	cmd->all = init_token1(cmd);
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

