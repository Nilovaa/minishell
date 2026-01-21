/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 09:55:27 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/21 21:35:35 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup_pipe_error(t_pars *pars, int fd[2])
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	ft_cleanup_heredocs(pars->redir);
	ft_cleanup_heredocs(pars->next->redir);
	pars->return_value = 1;
}

pid_t	ft_fork_first_child(t_pars *pars, t_cmd *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_cleanup_pipe_error(pars, fd);
		return (-1);
	}
	if (pid == 0)
		ft_first_child(pars, cmd, fd);
	return (pid);
}

pid_t	ft_fork_second_child(t_pars *pars, t_cmd *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_cleanup_pipe_error(pars, fd);
		return (-1);
	}
	if (pid == 0)
		ft_second_child(pars->next, cmd, fd);
	return (pid);
}

void	ft_wait_and_cleanup(t_pars *pars, pid_t pid1, pid_t pid2)
{
	int	status;

	ft_signal_ignore();
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	ft_signal_interactive();
	ft_cleanup_heredocs(pars->redir);
	ft_cleanup_heredocs(pars->next->redir);
	if (WIFEXITED(status))
		pars->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pars->return_value = 128 + WTERMSIG(status);
}

void	ft_execute_pipe(t_pars *pars, t_cmd *cmd, int fd[2])
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = ft_fork_first_child(pars, cmd, fd);
	if (pid1 == -1)
		return ;
	pid2 = ft_fork_second_child(pars, cmd, fd);
	if (pid2 == -1)
		return ;
	close(fd[0]);
	close(fd[1]);
	ft_wait_and_cleanup(pars, pid1, pid2);
}
