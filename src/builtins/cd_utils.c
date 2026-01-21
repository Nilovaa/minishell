/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:24:02 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 22:06:34 by andriamr         ###   ########.fr       */
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
