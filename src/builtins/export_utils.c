/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:37:52 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:40:17 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_find_var(t_cmd *cmd, char *name)
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
