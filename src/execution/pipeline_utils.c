/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:15:52 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/22 19:50:09 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_setup_redirections_utils(t_child_data	*data)
{
	perror("dup2 stdout");
	if (data->pids)
		free(data->pids);
	ft_free_pipes(data->pipes, data->nb_cmds - 1);
	if (data->cmd && data->cmd->cmd_base)
		free_all(data->cmd->cmd_base);
	if (data->cmd)
		free_all(data->cmd);
	exit(1);

}

void	ft_setup_redirections(t_child_data *data)
{
	if (data->index > 0)
	{
		if (dup2(data->pipes[data->index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			if (data->pids)
				free(data->pids);
			ft_free_pipes(data->pipes, data->nb_cmds - 1);
			if (data->cmd && data->cmd->cmd_base)
				free_all(data->cmd->cmd_base);
			if (data->cmd)
				free_all(data->cmd);
			exit(1);
		}
	}
	if (data->index < data->nb_cmds - 1)
	{
		if (dup2(data->pipes[data->index][1], STDOUT_FILENO) == -1)
		{
			ft_setup_redirections_utils(data);
			// perror("dup2 stdout");
			// if (data->pids)
			// 	free(data->pids);
			// ft_free_pipes(data->pipes, data->nb_cmds - 1);
			// if (data->cmd && data->cmd->cmd_base)
			// 	free_all(data->cmd->cmd_base);
			// if (data->cmd)
			// 	free_all(data->cmd);
			// exit(1);
		}
	}
}

static void	ft_free_partial_pipes(int **pipes, int count)
{
	while (--count >= 0)
		free(pipes[count]);
	free(pipes);
}

static int	ft_init_single_pipe(int **pipes, int index)
{
	pipes[index] = malloc(sizeof(int) * 2);
	if (!pipes[index])
		return (-1);
	if (pipe(pipes[index]) == -1)
	{
		perror("pipe");
		free(pipes[index]);
		return (-1);
	}
	return (0);
}

int	**ft_create_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	if (nb_pipes <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		if (ft_init_single_pipe(pipes, i) == -1)
		{
			ft_free_partial_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
