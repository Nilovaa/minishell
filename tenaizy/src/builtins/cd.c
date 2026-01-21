/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:47:52 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/21 21:46:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_env_value(char **env, char *var)
{
	int		i;
	int		len;

	if (!env || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	ft_cd_home(t_pars *pars, t_cmd *cmd)
{
	char	*path;

	if (!pars->arg || !pars->arg[0])
	{
		path = ft_get_env_value(cmd->env, "HOME");
		return (ft_change_to_dir(path, pars, cmd));
	}
	if (ft_strncmp(pars->arg[0], "~", 2) == 0 && !pars->arg[0][1])
	{
		path = ft_get_env_value(cmd->env, "HOME");
		return (ft_change_to_dir(path, pars, cmd));
	}
	return (-1);
}

static int	ft_cd_after_home(t_pars *pars, t_cmd *cmd)
{
	char	*path;

	if (ft_strncmp(pars->arg[0], "-", 2) == 0)
	{
		path = ft_get_env_value(cmd->env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			pars->return_value = 1;
			return (1);
		}
		ft_putendl_fd(path, 1);
		return (ft_change_to_dir(path, pars, cmd));
	}
	return (ft_change_to_dir(pars->arg[0], pars, cmd));
}

int	ft_cd(t_pars *pars, t_cmd *cmd)
{
	int	home_result;

	if (!pars)
		return (1);
	if (pars->arg[1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		pars->return_value = 1;
		return (1);
	}
	home_result = ft_cd_home(pars, cmd);
	if (home_result != -1)
		return (home_result);
	return (ft_cd_after_home(pars, cmd));
}
