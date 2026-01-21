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

static char	*ft_get_path(t_pars *pars, t_cmd *cmd)
{
	char	*path;

	path = ft_make_path(pars, cmd);
	if (!path)
	{
		pars->return_value = 127;
		return (NULL);
	}
	return (path);
}

static char	**ft_get_argv(t_pars *pars, char *path)
{
	char	**argv;

	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		pars->return_value = 1;
		return (NULL);
	}
	return (argv);
}

static int	ft_handle_heredoc(t_pars *pars, char *path, char **argv)
{
	if (ft_process_heredocs(pars->redir) < 0)
	{
		free(path);
		ft_free_split(argv);
		pars->return_value = 1;
		return (-1);
	}
	return (0);
}

static void	ft_child_exec(char *path, char **argv, t_pars *pars, t_cmd *cmd)
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
	exit(1);
}

static pid_t	ft_exec(char *path, char **argv, t_pars *pars, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		pars->return_value = 1;
		free(path);
		ft_free_split(argv);
		ft_cleanup_heredocs(pars->redir);
		return (-1);
	}
	if (pid == 0)
		ft_child_exec(path, argv, pars, cmd);
	return (pid);
}

static void	ft_parent_wait(pid_t pid, t_pars *pars, char *path, char **argv)
{
	int	status;

	ft_signal_ignore();
	waitpid(pid, &status, 0);
	ft_signal_interactive();
	ft_cleanup_heredocs(pars->redir);
	if (WIFEXITED(status))
		pars->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pars->return_value = 128 + WTERMSIG(status);
	free(path);
	free(argv);
}

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**argv;
	pid_t	pid;

	if (!pars || !pars->cmd)
		return ;
	path = ft_get_path(pars, cmd);
	if (!path)
		return ;
	argv = ft_get_argv(pars, path);
	if (!argv)
	{
		free(path);
		return ;
	}
	if (ft_handle_heredoc(pars, path, argv) < 0)
		return ;
	pid = ft_exec(path, argv, pars, cmd);
	if (pid == -1)
		return ;
	ft_parent_wait(pid, pars, path, argv);
}
