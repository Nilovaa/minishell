/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:16:47 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/21 21:46:46 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_get_argv(t_pars *pars, char *path)
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

int	ft_handle_heredoc(t_pars *pars, char *path, char **argv, t_cmd *cmd)
{
	if (ft_process_heredocs(pars->redir, cmd) < 0)
	{
		free(path);
		ft_free_split(argv);
		ft_cleanup_heredocs(pars->redir);
		pars->return_value = 130;
		return (-1);
	}
	return (0);
}

void	ft_child_exec(char *path, char **argv, t_pars *pars, t_cmd *cmd)
{
	ft_signal_child();
	if (ft_redirection(pars->redir, cmd, 1) < 0)
	{
		free(path);
		free(argv);
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	execve(path, argv, cmd->env);
	perror("execve");
	free(path);
	free(argv);
	if (cmd && cmd->cmd_base)
		free_all(cmd->cmd_base);
	free_all(cmd);
	exit(1);
}

pid_t	ft_exec(char *path, char **argv, t_pars *pars, t_cmd *cmd)
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

void	ft_parent_wait(pid_t pid, t_pars *pars, char *path, char **argv)
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
