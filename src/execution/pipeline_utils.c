/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:15:52 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/07 00:15:56 by nyrakoto         ###   ########.fr       */
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

void	ft_setup_redirections(int **pipes, int index, int nb_cmds)
{
	if (index > 0)
	{
		if (dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(1);
		}
	}
	if (index < nb_cmds - 1)
	{
		if (dup2(pipes[index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
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
