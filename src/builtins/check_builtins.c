/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:25:13 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/16 16:28:36 by andriamr         ###   ########.fr       */
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
		ret = ft_cd(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "echo", 5) && pars->cmd[4] == '\0')
		ret = ft_echo(pars);
	else if (!ft_strncmp(pars->cmd, "env", 4) && pars->cmd[3] == '\0')
		ret = ft_env(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "exit", 5) && pars->cmd[4] == '\0')
		ret = ft_exit(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "export", 7) && pars->cmd[6] == '\0')
		ret = ft_export(pars, cmd);
	else if (!ft_strncmp(pars->cmd, "pwd", 4) && pars->cmd[3] == '\0')
		ret = ft_pwd(pars);
	else if (!ft_strncmp(pars->cmd, "unset", 6) && pars->cmd[5] == '\0')
		ret = ft_unset(pars, cmd);
	pars->return_value = ret;
	return (ret);
}

static void	ft_no_cmd(t_pars *pars, t_cmd *cmd)
{
	int	in;
	int	out;

	if (ft_process_heredocs(pars->redir, cmd) < 0)
	{
		ft_cleanup_heredocs(pars->redir);
		pars->return_value = 130;
		return ;
	}
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (ft_redirection(pars->redir, NULL, 0) < 0)
		pars->return_value = 1;
	else
		pars->return_value = 0;
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	ft_cleanup_heredocs(pars->redir);
}

static void	ft_builtin(t_pars *pars, t_cmd *cmd)
{
	int	stdin_backup;
	int	stdout_backup;

	if (ft_process_heredocs(pars->redir, cmd) < 0)
	{
		ft_cleanup_heredocs(pars->redir);
		pars->return_value = 130;
		return ;
	}
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_redirection(pars->redir, NULL, 0) < 0)
	{
		close(stdin_backup);
		close(stdout_backup);
		ft_cleanup_heredocs(pars->redir);
		pars->return_value = 1;
		return ;
	}
	ft_exec_builtin_only(pars, cmd);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	ft_cleanup_heredocs(pars->redir);
}

void	ft_check_builtins(t_pars *pars, t_cmd *cmd)
{
	if (!pars || !cmd)
		return ;
	if (pars->next)
	{
		ft_exec_pipeline(pars, cmd);
		return ;
	}
	if (!pars->cmd)
	{
		ft_no_cmd(pars, cmd);
		return ;
	}
	if (ft_is_builtin(pars->cmd))
	{
		ft_builtin(pars, cmd);
		return ;
	}
	ft_exec_simple(pars, cmd);
}
