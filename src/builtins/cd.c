/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:47:52 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:49 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_env_value(char **env, char *var)
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

static void	ft_update_oldpwd(t_cmd *cmd, char *oldpwd)
{
	int		i;
	char	*new_var;

	if (!cmd || !cmd->env)
		return ;
	new_var = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_var)
		return ;
	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], "OLDPWD=", 7) == 0)
		{
			free(cmd->env[i]);
			cmd->env[i] = new_var;
			return ;
		}
		i++;
	}
	free(new_var);
}

static void	ft_update_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	char	*new_var;
	int		i;

	if (!cmd || !cmd->env)
		return ;
	if (!getcwd(cwd, PATH_MAX))
		return ;
	new_var = ft_strjoin("PWD=", cwd);
	if (!new_var)
		return ;
	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], "PWD=", 4) == 0)
		{
			free(cmd->env[i]);
			cmd->env[i] = new_var;
			return ;
		}
		i++;
	}
	free(new_var);
}

static int	ft_change_to_dir(char *path, t_pars *pars, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		has_cwd;

	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		pars->return_value = 1;
		return (1);
	}
	has_cwd = (getcwd(cwd, PATH_MAX) != NULL);
	if (chdir(path) != 0)
	{
		perror("cd");
		pars->return_value = 1;
		return (1);
	}
	if (has_cwd)
		ft_update_oldpwd(cmd, cwd);
	ft_update_pwd(cmd);
	pars->return_value = 0;
	return (0);
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

int	ft_cd(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	int		home_result;

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
