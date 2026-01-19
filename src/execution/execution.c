/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:16:47 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/27 18:20:44 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	pid_t		pid;
	char		*path;
	char		**argv;
	int			status;

	if (!pars || !pars->cmd)
		return ;
	path = ft_make_path(pars, cmd);
	if (!path)
	{
		pars->return_value = 127;
		return ;
	}
	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		pars->return_value = 1;
		return ;
	}
	if (ft_process_heredocs(pars->redir) < 0)
	{
		free(path);
		ft_free_split(argv);
		pars->return_value = 1;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		pars->return_value = 1;
		free(path);
		ft_free_split(argv);
		ft_cleanup_heredocs(pars->redir);
		return ;
	}
	if (pid == 0)
	{
		ft_signal_child();
		if (ft_redirection(pars->redir) < 0)
		{
			free(path);
			ft_free_split(argv);
			exit(1);
		}
		execve(path, argv, cmd->env);
		perror("execve");
		free(path);
		ft_free_split(argv);
		exit (1);
	}
	else
	{
		ft_signal_ignore();
		waitpid(pid, &status, 0);
		ft_signal_interactive();
		ft_cleanup_heredocs(pars->redir);
		if (WIFEXITED(status))
			pars->return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			pars->return_value = 128 + WTERMSIG(status);
	}
	free(path);
	free(argv);
}
