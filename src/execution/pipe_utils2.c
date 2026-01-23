/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:34:48 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 04:02:28 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_second_child(t_pars *pars, t_cmd *cmd, int fd[2])
{
	close(fd[1]);
	ft_signal_child();
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	close(fd[0]);
	if (ft_redirection(pars->redir, cmd, 1) < 0)
	{
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	ft_exec_child_command(pars, cmd);
}

static void	ft_exec_child_command_utils(char *path, char **arg, t_cmd *cmd)
{
	if (path)
		free(path);
	if (arg)
		free(arg);
	if (cmd && cmd->cmd_base)
		free_all(cmd->cmd_base);
	free_all(cmd);
	exit(127);
}

static void	ft_command_utils2(char *path, t_cmd *cmd, t_pars *pars)
{
	char	**arg;

	path = ft_make_path(pars, cmd);
	arg = ft_make_args(pars);
	if (!path || !arg)
		ft_exec_child_command_utils(path, arg, cmd);
	execve(path, arg, cmd->env);
	perror("execve");
	free(path);
	free(arg);
	if (cmd && cmd->cmd_base)
		free_all(cmd->cmd_base);
	free_all(cmd);
}

void	ft_exec_child_command(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	int		ret;

	path = NULL;
	if (!pars->cmd || !pars->cmd[0])
	{
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(0);
	}
	if (ft_is_builtin(pars->cmd))
	{
		ret = ft_exec_builtin_only(pars, cmd);
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(ret);
	}
	ft_command_utils2(path, cmd, pars);
	exit(1);
}
