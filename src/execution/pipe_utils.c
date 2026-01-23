/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:29:46 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 21:41:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_first_child(t_pars *pars, t_cmd *cmd, int fd[2])
{
	close(fd[0]);
	ft_signal_child();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	close(fd[1]);
	if (ft_redirection(pars->redir, cmd, 1) < 0)
	{
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	ft_exec_child_command(pars, cmd);
}

int	ft_check_pipe_params(t_pars *pars)
{
	if (!pars || !pars->next)
	{
		if (pars)
			pars->return_value = 1;
		return (-1);
	}
	return (0);
}

int	ft_create_pipe(t_pars *pars, int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		ft_cleanup_heredocs(pars->redir);
		ft_cleanup_heredocs(pars->next->redir);
		pars->return_value = 1;
		return (-1);
	}
	return (0);
}

int	ft_prepare_heredocs(t_pars *pars, t_cmd *cmd)
{
	if (ft_process_heredocs(pars->redir, cmd) < 0
		|| ft_process_heredocs(pars->next->redir, cmd) < 0)
	{
		ft_cleanup_heredocs(pars->redir);
		ft_cleanup_heredocs(pars->next->redir);
		pars->return_value = 1;
		return (-1);
	}
	return (0);
}

void	ft_exec_simple_pipe(t_pars *pars, t_cmd *cmd)
{
	int	fd[2];

	if (ft_check_pipe_params(pars) < 0)
		return ;
	if (ft_prepare_heredocs(pars, cmd) < 0)
		return ;
	if (ft_create_pipe(pars, fd) < 0)
		return ;
	ft_execute_pipe(pars, cmd, fd);
}
