/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 09:55:27 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/04 09:55:32 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/types.h>
#include <uchar.h>

static void	ft_exec_child_command(t_pars *pars, t_cmd *cmd)
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

void	ft_first_child(t_pars *pars, t_cmd *cmd, int fd[2])
{
	close(fd[0]);
	ft_signal_child();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[1]);
	if (ft_redirection(pars->redir) < 0)
		exit(1);
	ft_exec_child_command(pars, cmd);
}

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

static void	ft_cleanup_pipe_error(t_pars *pars, int fd[2])
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	ft_cleanup_heredocs(pars->redir);
	ft_cleanup_heredocs(pars->next->redir);
	pars->return_value = 1;
}

static int	ft_create_pipe(t_pars *pars, int fd[2])
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

static pid_t	ft_fork_first_child(t_pars *pars, t_cmd *cmd, int fd[2])
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

static pid_t	ft_fork_second_child(t_pars *pars, t_cmd *cmd, int fd[2])
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

static void	ft_wait_and_cleanup(t_pars *pars, pid_t pid1, pid_t pid2)
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

static int	ft_check_pipe_params(t_pars *pars)
{
	if (!pars || !pars->next || !pars->cmd || !pars->next->cmd)
	{
		if (pars)
			pars->return_value = 1;
		return (-1);
	}
	return (0);
}

static int	ft_prepare_heredocs(t_pars *pars)
{
	if (ft_process_heredocs(pars->redir) < 0
		|| ft_process_heredocs(pars->next->redir) < 0)
	{
		ft_cleanup_heredocs(pars->redir);
		ft_cleanup_heredocs(pars->next->redir);
		pars->return_value = 1;
		return (-1);
	}
	return (0);
}

static void	ft_execute_pipe(t_pars *pars, t_cmd *cmd, int fd[2])
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

void	ft_exec_simple_pipe(t_pars *pars, t_cmd *cmd)
{
	int	fd[2];

	if (ft_check_pipe_params(pars) < 0)
		return ;
	if (ft_prepare_heredocs(pars) < 0)
		return ;
	if (ft_create_pipe(pars, fd) < 0)
		return ;
	ft_execute_pipe(pars, cmd, fd);
}
