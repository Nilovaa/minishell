/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:50:28 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 21:52:18 by andriamr         ###   ########.fr       */
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
