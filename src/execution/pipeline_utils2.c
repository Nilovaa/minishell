/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:50:28 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/22 19:46:39 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_child_resources(t_child_data *data)
{
	if (data->pids)
		free(data->pids);
	ft_free_pipes(data->pipes, data->nb_cmds - 1);
	if (data->cmd && data->cmd->cmd_base)
		free_all(data->cmd->cmd_base);
}

static void	ft_exec_command(t_child_data *data)
{
	char	*path;
	char	**argv;

	path = ft_make_path(data->pars, data->cmd);
	argv = ft_make_args(data->pars);
	if (!path || !argv)
	{
		if (path)
			free(path);
		if (argv)
			free(argv);
		ft_putstr_fd("command not found\n", 2);
		ft_free_child_resources(data);
		free_all(data->cmd);
		exit(127);
	}
	execve(path, argv, data->cmd->env);
	perror("execve");
	free(path);
	free(argv);
	ft_free_child_resources(data);
	free_all(data->cmd);
	exit(126);
}

void	ft_child_process(t_child_data *data)
{
	int	ret;

	ft_signal_child();
	ft_setup_redirections(data);
	ft_close_all_pipes(data->pipes, data->nb_cmds - 1);
	if (ft_redirection(data->pars->redir, data->cmd, 1) < 0)
	{
		ft_free_child_resources(data);
		free_all(data->cmd);
		exit(1);
	}
	if (ft_is_builtin(data->pars->cmd))
	{
		ret = ft_exec_builtin_only(data->pars, data->cmd);
		ft_free_child_resources(data);
		free_all(data->cmd);
		exit(ret);
	}
	ft_exec_command(data);
}

void	ft_cleanup_all_heredocs(t_pars *pars)
{
	t_pars	*current;

	current = pars;
	while (current)
	{
		ft_cleanup_heredocs(current->redir);
		current = current->next;
	}
}

void	ft_free_pipes(int **pipes, int nb_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_pipes)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}
