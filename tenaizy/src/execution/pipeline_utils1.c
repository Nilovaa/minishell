/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:48:41 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 22:06:00 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_cmds(t_pars *pars)
{
	int		count;
	t_pars	*tmp;

	count = 0;
	tmp = pars;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_close_all_pipes(int **pipes, int nb_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_pipes)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
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

pid_t	ft_fork_single_process(t_fork_data *data, int i)
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
