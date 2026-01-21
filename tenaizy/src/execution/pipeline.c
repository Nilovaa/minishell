/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:03:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/21 21:52:05 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
