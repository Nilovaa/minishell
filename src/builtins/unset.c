/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 01:36:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/23 03:55:26 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_find_var(char **env, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**ft_remove_var(char **env, int index_env)
{
	int		i;
	int		j;
	char	**dest_env;

	i = 0;
	while (env[i])
		i++;
	dest_env = malloc(sizeof(char *) * i);
	if (!dest_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index_env)
		{
			dest_env[j] = ft_strdup(env[i]);
			if (!dest_env[j])
				return (NULL);
			j++;
		}
		i++;
	}
	dest_env[j] = NULL;
	return (dest_env);
}

static int	ft_process_unset(t_cmd *cmd, t_pars *pars, char *var_name)
{
	int		index_env;
	char	**dest_env;

	index_env = ft_find_var(cmd->env, var_name);
	if (index_env >= 0)
	{
		dest_env = ft_remove_var(cmd->env, index_env);
		if (!dest_env)
		{
			pars->return_value = 1;
			return (1);
		}
		ft_free_split(cmd->env);
		cmd->env = dest_env;
	}
	return (0);
}

int	ft_unset(t_pars *pars, t_cmd *cmd)
{
	int	i;
	int	check;

	if (!pars || !pars->arg || !pars->arg[0])
	{
		pars->return_value = 0;
		return (0);
	}
	i = 0;
	check = 0;
	while (pars->arg[i])
	{
		if (!ft_check_name(pars->arg[i]))
		{
			ft_putstr_fd("unset: not a valid identifier\n", 2);
			check = 1;
		}
		else if (ft_process_unset(cmd, pars, pars->arg[i]))
			return (1);
		i++;
	}
	pars->return_value = check;
	return (check);
}
