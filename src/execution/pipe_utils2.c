/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:34:48 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 21:35:46 by andriamr         ###   ########.fr       */
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
		exit(1);
	}
	close(fd[0]);
	if (ft_redirection(pars->redir) < 0)
		exit(1);
	ft_exec_child_command(pars, cmd);
}

void	ft_exec_child_command(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**arg;
	int		ret;

	if (ft_is_builtin(pars->cmd))
	{
		ret = ft_exec_builtin_only(pars, cmd);
		exit(ret);
	}
	path = ft_make_path(pars, cmd);
	arg = ft_make_args(pars);
	if (!path || !arg)
	{
		if (path)
			free(path);
		if (arg)
			ft_free_split(arg);
		exit(127);
	}
	execve(path, arg, cmd->env);
	perror("execve");
	free(path);
	ft_free_split(arg);
	exit(1);
}
