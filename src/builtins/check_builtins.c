/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:25:13 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/05 10:43:55 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 3) && cmd[2] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "echo", 5) && cmd[4] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "env", 4) && cmd[3] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "exit", 5) && cmd[4] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "export", 7) && cmd[6] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4) && cmd[3] == '\0')
		return (1);
	if (!ft_strncmp(cmd, "unset", 6) && cmd[5] == '\0')
		return (1);
	return (0);
}

int	ft_exec_builtin_only(t_pars *pars, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(pars->cmd, "cd", 3) && pars->cmd[2] == '\0')
		ret = ft_cd(pars);
	else if (!ft_strncmp(pars->cmd, "echo", 5) && pars->cmd[4] == '\0')
		ret = ft_echo(pars);
	else if (!ft_strncmp(pars->cmd, "env", 4) && pars->cmd[3] == '\0')
		ret = ft_env(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "exit", 5) && pars->cmd[4] == '\0')
		ft_exit(pars);
	else if (!ft_strncmp(pars->cmd, "export", 7) && pars->cmd[6] == '\0')
		ret = ft_export(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "pwd", 4) && pars->cmd[3] == '\0')
		ret = ft_pwd(pars);
	else if (!ft_strncmp(pars->cmd, "unset", 6) && pars->cmd[5] == '\0')
		ret = ft_unset(pars, cmd);
	pars->return_value = ret;
	return (ret);
}

void	ft_check_builtins(t_pars *pars, t_cmd *cmd)
{
	if (!pars || !pars->cmd || !cmd)
		return ;
	if (pars->next)
	{
		ft_exec_pipeline(pars, cmd);
		return ;
	}
	if (ft_is_builtin(pars->cmd))
	{
		ft_exec_builtin_only(pars, cmd);
		return ;
	}
	ft_exec_simple(pars, cmd);
}
