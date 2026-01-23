/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:24:02 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 03:54:16 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_update_pwd(t_cmd *cmd)
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

void	ft_update_oldpwd(t_cmd *cmd, char *oldpwd)
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

int	ft_valid_name(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_export(t_pars *pars, t_cmd *cmd, int j)
{
	if (!ft_valid_name(pars->arg[j]))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		pars->return_value = 1;
		return (1);
	}
	if (!ft_strchr(pars->arg[j], '='))
		return (0);
	if (ft_update(cmd, pars, pars->arg[j]))
		return (1);
	return (0);
}
