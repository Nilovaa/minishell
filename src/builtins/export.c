/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:49:23 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:41 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_var(t_cmd *cmd, char *name)
{
	int	i;
	int	len;
	char	**env;

	len = 0;
	i = 0;
	while (name[len] && name[len] != '=')
		len++;
	env = ft_listtochar(cmd->env_list);
	if (!env)
		return (-1);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			ft_free_split(env);
			return (i);
		}
		i++;
	}
	ft_free_split(env);
	return (-1);
}

static char **ft_add_var(t_cmd *cmd, char *var)
{
	char	**dest_env;
	char	**env;
	int		i;

	env = ft_listtochar(cmd->env_list);
	if (!env)
		return (NULL);
	i = 0;
	while (env && env[i])
		i++;
	dest_env = malloc(sizeof(char *) * (i + 2));
	if (!dest_env)
	{
		ft_free_split(env);
		return (NULL);
	}
	i = 0;
	while (env && env[i])
	{
		dest_env[i] = ft_strdup(env[i]);
		if (!dest_env[i])
		{
			ft_free_split(env);
			return (NULL);
		}
		i++;
	}
	dest_env[i] = ft_strdup(var);
	if (!dest_env[i])
	{
		ft_free_split(env);
		return (NULL);
	}
	dest_env[i + 1] = NULL;
	ft_free_split(env);
	return (dest_env);
}

int	ft_export(t_pars *pars, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**dest_env;

	if (!pars || !pars->arg)
	{
		pars->return_value = 0;
		return (0);
	}
	if (!pars->arg[0])
	{
		pars->return_value = 0;
		return (0);
	}
	j = 0;
	while (pars->arg[j])
	{
		if (!ft_strchr(pars->arg[j], '='))
		{
			ft_putstr_fd("export: invalid format\n", 2);
			pars->return_value = 1;
			j++;
			continue;
		}
		i = ft_find_var(cmd, pars->arg[j]);
		if (i >= 0)
		{
			free(cmd->env[i]);
			cmd->env[i] = ft_strdup(pars->arg[j]);
		}
		else
		{
			dest_env = ft_add_var(cmd, pars->arg[j]);
			if (!dest_env)
			{
				pars->return_value = 0;
				return (1);
			}
			ft_free_split(cmd->env);
			cmd->env = dest_env;
		}
		j++;
	}
	pars->return_value = 0;
	return (0);
}
