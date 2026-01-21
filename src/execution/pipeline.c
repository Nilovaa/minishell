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

static void	ft_exec_command(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**argv;

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

void	ft_child_process(t_child_data *data)
{
	int	ret;

	ft_signal_child();
	ft_setup_redirections(data->pipes, data->index, data->nb_cmds);
	ft_close_all_pipes(data->pipes, data->nb_cmds - 1);
	if (ft_redirection(data->pars->redir) < 0)
		exit(1);
	if (ft_is_builtin(data->pars->cmd))
	{
		ret = ft_exec_builtin_only(data->pars, data->cmd);
		exit(ret);
	}
	ft_exec_command(data->pars, data->cmd);
}

static pid_t	ft_fork_single_process(t_fork_data *data, int i)
{
	pid_t			pid;
	t_child_data	child;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		child.pars = data->pars;
		child.cmd = data->cmd;
		child.pipes = data->pipes;
		child.index = i;
		child.nb_cmds = data->nb_cmds;
		ft_child_process(&child);
	}
	return (pid);
}

pid_t	*ft_fork_processes(t_fork_data *data)
{
	pid_t	*pids;
	t_pars	*current;
	int		i;

	pids = malloc(sizeof(pid_t) * data->nb_cmds);
	if (!pids)
		return (NULL);
	current = data->pars;
	i = 0;
	while (i < data->nb_cmds && current)
	{
		data->pars = current;
		pids[i] = ft_fork_single_process(data, i);
		if (pids[i] == -1)
		{
			perror("fork");
			while (--i >= 0)
				kill(pids[i], SIGKILL);
			free(pids);
			return (NULL);
		}
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

static void	ft_cleanup_all_heredocs(t_pars *pars)
{
	t_pars	*current;

	current = pars;
	while (current)
	{
		ft_cleanup_heredocs(current->redir);
		current = current->next;
	}
}

static int	ft_prepare_all_heredocs(t_pars *pars)
{
	t_pars	*current;

	current = pars;
	while (current)
	{
		if (ft_process_heredocs(current->redir) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

static int	ft_handle_simple_cases(t_pars *pars, t_cmd *cmd, int nb_cmds)
{
	if (nb_cmds == 0)
		return (1);
	if (nb_cmds == 1)
	{
		ft_check_builtins(pars, cmd);
		return (1);
	}
	if (nb_cmds == 2)
	{
		ft_exec_simple_pipe(pars, cmd);
		return (1);
	}
	return (0);
}

static int	ft_setup_pipes(t_pars *pars, int nb_cmds, int ***pipes)
{
	*pipes = ft_create_pipes(nb_cmds - 1);
	if (!*pipes)
	{
		ft_cleanup_all_heredocs(pars);
		pars->return_value = 1;
		return (-1);
	}
	return (0);
}

static void	ft_execute_and_wait(t_pars *pars, t_cmd *cmd,
	int **pipes, int nb_cmds)
{
	pid_t		*pids;
	int			status;
	t_fork_data	data;

	data.pars = pars;
	data.cmd = cmd;
	data.pipes = pipes;
	data.nb_cmds = nb_cmds;
	pids = ft_fork_processes(&data);
	ft_close_all_pipes(pipes, nb_cmds - 1);
	if (!pids)
	{
		ft_free_pipes(pipes, nb_cmds - 1);
		ft_cleanup_all_heredocs(pars);
		pars->return_value = 1;
		return ;
	}
	ft_signal_ignore();
	status = ft_wait_all(pids, nb_cmds);
	ft_signal_interactive();
	ft_cleanup_all_heredocs(pars);
	pars->return_value = status;
	free(pids);
	ft_free_pipes(pipes, nb_cmds - 1);
}

void	ft_exec_pipeline(t_pars *pars, t_cmd *cmd)
{
	int	nb_cmds;
	int	**pipes;

	if (!pars || !cmd)
		return ;
	nb_cmds = ft_count_cmds(pars);
	if (ft_handle_simple_cases(pars, cmd, nb_cmds))
		return ;
	if (ft_prepare_all_heredocs(pars) < 0)
	{
		pars->return_value = 1;
		return ;
	}
	if (ft_setup_pipes(pars, nb_cmds, &pipes) < 0)
		return ;
	ft_execute_and_wait(pars, cmd, pipes, nb_cmds);
}
