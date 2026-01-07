/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:46:21 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/07 09:17:38 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*creat_list_env(char *env_line)
{
	t_env	*new;
	int		i;
	int		j;

	j = 0;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	new->key = ft_calloc(sizeof(char), i + 1);
	if (!new->key)
		return (NULL);
	while (env_line[j] && j < i)
	{
		new->key[j] = env_line[j];
		j++;
	}
	if (env_line[i] == '=')
		new->value = ft_strdup(&env_line[i + 1]);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_list_env(t_env *env, char *env_line)
{
	t_env	*first;
	t_env	*new;

	new = creat_list_env(env_line);
	if (!new)
		return ;
	if (env == NULL)
	{
		env = new;
		return ;
	}
	first = env;
	while (first->next != NULL)
		first = first->next;
	first->next = new;
	new->next = NULL;
}

void	init_env(t_cmd *cmd, char **envp)
{
	int i;

	i = 0;
	cmd->env = NULL;
	while (envp[i])
	{
		add_list_env(cmd->env, envp[i]);
		i++;
	}
}

t_cmd	*cpy_env_list(char **env)
{
	int i;
	t_cmd	*cmd_base;
	t_env *tmp;
	
	i = 0;
	cmd_base = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd_base)
		return (NULL);
	tmp = NULL;
	while (env[i])
	{	
		add_list_env(tmp, env[i]);
		i++;
	}
	cmd_base->env = tmp;
	return (cmd_base);
}