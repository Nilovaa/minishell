/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:03:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/05 23:03:37 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_child_process(t_pars *pars, t_cmd *cmd, int **pipes, int index, int nb_cmds)
{
	char	*path;
	char	**argv;
	int		ret;

	ft_signal_child();
	ft_setup_redirections(pipes, index, nb_cmds);
	ft_close_all_pipes(pipes, nb_cmds - 1);
	if (ft_redirection(pars->redir) < 0)
		exit (1);
	if (ft_is_builtin(pars->cmd))
	{
		ret = ft_exec_builtin_only(pars, cmd);
		exit(ret);
	}
	path = ft_make_path(pars, cmd);
	argv = ft_make_args(pars);
	if (!path || !argv)
	{
		if (path)
			free(path);
		if (argv)
			ft_free_split(argv);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	execve(path, argv, cmd->env);
	perror("execve");
	free(path);
	ft_free_split(argv);
	exit(126);
}

pid_t	*ft_fork_processes(t_pars *pars, t_cmd *cmd, int **pipes, int nb_cmds)
{
	pid_t	*pids;
	t_pars	*current;
	int		i;

	pids = malloc(sizeof(pid_t) * nb_cmds);
	if (!pids)
		return (NULL);
	current = pars;
	i = 0;
	while (i < nb_cmds && current)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			while (--i >= 0)
				kill(pids[i], SIGKILL);
			free(pids);
			return (NULL);
		}
		if (pids[i] == 0)
			ft_child_process(current, cmd, pipes, i, nb_cmds);
		current = current->next;
		i++;
	}
	return (pids);
}

int	ft_wait_all(pid_t *pids, int nb_cmds)
{
	int	status;
	int	i;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < nb_cmds)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			i++;
			continue ;
		}
		if (i == nb_cmds - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

void	ft_exec_pipeline(t_pars *pars, t_cmd *cmd)
{
	int		nb_cmds;
	int		**pipes;
	pid_t	*pids;
	int		status;
	t_pars	*current;

	if (!pars || !cmd)
		return ;
	nb_cmds = ft_count_cmds(pars);
	if (nb_cmds == 0)
		return ;
	if (nb_cmds == 1)
	{
		ft_check_builtins(pars, cmd);
		return ;
	}
	if (nb_cmds == 2)
	{
		ft_exec_simple_pipe(pars, cmd);
		return ;
	}
	current = pars;
	while (current)
	{
		if (ft_process_heredocs(current->redir) < 0)
		{
			pars->return_value = 1;
			return ;
		}
		current = current->next;
	}
	pipes = ft_create_pipes(nb_cmds - 1);
	if (!pipes)
	{
		current = pars;
		while (current)
		{
			ft_cleanup_heredocs(current->redir);
			current = current->next;
		}
		pars->return_value = 1;
		return ;
	}
	pids = ft_fork_processes(pars, cmd, pipes, nb_cmds);
	ft_close_all_pipes(pipes, nb_cmds - 1);
	if (!pids)
	{
		ft_free_pipes(pipes, nb_cmds - 1);
		current = pars;
		while (current)
		{
			ft_cleanup_heredocs(current->redir);
			current = current->next;
		}
		pars->return_value = 1;
		return ;
	}
	ft_signal_ignore();
	status = ft_wait_all(pids, nb_cmds);
	ft_signal_interactive();
	current = pars;
	while (current)
	{
		ft_cleanup_heredocs(current->redir);
		current = current->next;
	}
	pars->return_value = status;
	free(pids);
	ft_free_pipes(pipes, nb_cmds - 1);
}
