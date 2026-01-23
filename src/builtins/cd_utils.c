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

// int	ft_find_var(t_cmd *cmd, char *name)
// {
// 	int	i;
// 	int	len;

// 	len = 0;
// 	i = 0;
// 	while (name[len] && name[len] != '=')
// 		len++;
// 	while (cmd->env && cmd->env[i])
// 	{
// 		if (!ft_strncmp(cmd->env[i], name, len) && cmd->env[i][len] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }
