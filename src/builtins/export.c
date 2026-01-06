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

	len = 0;
	i = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (cmd->env && cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], name, len) && cmd->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char **ft_add_var(t_cmd *cmd, char *var)
{
	char	**dest_env;
	int		i;

	i = 0;
	while (cmd->env && cmd->env[i])
		i++;
	dest_env = malloc(sizeof(char *) * (i + 2));
	if (!dest_env)
		return (NULL);
	i = 0;
	while (cmd->env && cmd->env[i])
	{
		dest_env[i] = ft_strdup(cmd->env[i]);
		if (!dest_env[i])
			return (NULL);
		i++;
	}
	dest_env[i] = ft_strdup(var);
	if (!dest_env[i])
		return (NULL);
	dest_env[i + 1] = NULL;
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
