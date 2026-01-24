/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:49:23 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/09 17:27:38 by andriamr         ###   ########.fr       */
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

static char	**ft_add_var(t_cmd *cmd, char *var)
{
	char	**dest_env;
	int		i;
	int		j;

	i = 0;
	while (cmd->env && cmd->env[i])
		i++;
	dest_env = malloc(sizeof(char *) * (i + 2));
	if (!dest_env)
		return (NULL);
	j = 0;
	while (cmd->env && cmd->env[j])
	{
		dest_env[j] = ft_strdup(cmd->env[j]);
		if (!dest_env[j])
		{
			while (--j >= 0)
				free(dest_env[j]);
			return (free(dest_env), NULL);
		}
		j++;
	}
	dest_env[j] = ft_strdup(var);
	if (!dest_env[j])
	{
		while (--j >= 0)
			free(dest_env[j]);
		return (free(dest_env), NULL);
	}
	dest_env[j + 1] = NULL;
	return (dest_env);
}

int	ft_update(t_cmd *cmd, t_pars *pars, char *arg)
{
	int		i;
	char	**dest_env;

	i = ft_find_var(cmd, arg);
	if (i >= 0)
	{
		free(cmd->env[i]);
		cmd->env[i] = ft_strdup(arg);
	}
	else
	{
		dest_env = ft_add_var(cmd, arg);
		if (!dest_env)
		{
			pars->return_value = 0;
			return (1);
		}
		ft_free_split(cmd->env);
		cmd->env = dest_env;
	}
	return (0);
}

static int	ft_no_arg(t_pars *pars, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!pars->arg[0])
	{
		pars->return_value = 0;
		while (cmd && cmd->env && cmd->env[i])
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(cmd->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_export(t_pars *pars, t_cmd *cmd)
{
	int	j;

	if (!pars || !pars->arg)
	{
		pars->return_value = 0;
		return (0);
	}
	if (ft_no_arg(pars, cmd))
		return (0);
	j = 0;
	while (pars->arg[j])
	{
		if (ft_arg_export(pars, cmd, j))
			return (1);
		j++;
	}
	pars->return_value = 0;
	return (0);
}
