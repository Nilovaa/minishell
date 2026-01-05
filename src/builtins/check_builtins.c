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

void	ft_check_builtins(t_pars *pars, char **env)
{
	if(!ft_strncmp(pars->cmd, "cd", 2))
		ft_cd(pars);
	else if (!ft_strncmp(pars->cmd, "echo", 4))
		ft_echo(pars);
	else if (!ft_strncmp(pars->cmd, "env", 3))
		ft_env(pars, env);
	else if (!ft_strncmp(pars->cmd, "exit", 4))
		ft_exit(pars);
	else if (!ft_strncmp(pars->cmd, "export", 6))
		ft_export(pars, &env);
	else if (!ft_strncmp(pars->cmd, "pwd", 3))
		ft_pwd(pars);
	else if (!ft_strncmp(pars->cmd, "unset", 5))
		ft_unset(pars, &env);
	else
	{
		if (!pars->next)
			ft_exec_simple(pars, env);
		else if (pars->next)
			ft_exec_simple_pipe(pars, env);
	}
}
