/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:46:21 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/05 16:57:28 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*creat_list_env(char *env_line)
{
	t_env	*new;
	char	*key;
	int		i;
	int		j;

	j = 0;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), i + 1);
	if (!key)
		return (NULL);
	while (env_line[j] && j < i)
	{
		key[j] = env_line[j];
		j++;
	}
	key[j] = '\0';
	new->key = key;
	if (env_line[i] == '=')
		new->value = ft_strdup(&env_line[i + 1]);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_list_env(t_env *env, char *env_line)
{
	t_env	*last;
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
