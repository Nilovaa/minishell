/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 01:36:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/24 20:49:42 by andriamr         ###   ########.fr       */
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

static int	copy_env_except(char **dest, char **src, int skip_idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (i != skip_idx)
		{
			dest[j] = ft_strdup(src[i]);
			if (!dest[j])
				return (free_env_error(dest, j));
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (1);
}

static char	**ft_remove_var(char **env, int index_env)
{
	char	**dest_env;
	int		len;

	len = 0;
	while (env[len])
		len++;
	dest_env = malloc(sizeof(char *) * len);
	if (!dest_env)
		return (NULL);
	if (!copy_env_except(dest_env, env, index_env))
		return (NULL);
	return (dest_env);
}

static int	ft_process_unset(t_cmd *cmd, t_pars *pars, char *var_name)
{
	int		index_env;
	char	**dest_env;

	index_env = ft_find_var1(cmd->env, var_name);
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
