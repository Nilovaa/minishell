/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:03:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 12:42:37 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"
#include <stdlib.h>

void	ft_exit(void)
{
	exit (1);
}

void	free_cmd2(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free (dest[i]);
		i++;
	}
	free (dest);
	dest = NULL;
}

void	free_redir(t_dir *redir)
{
	if (redir->dir_in)
	{
		if (redir->file_in)
			free_cmd2(redir->file_in);
	}
	if (redir->dir_out)
	{
		if (redir->file_out)
			free_cmd2(redir->file_out);
	}
	if (redir->dir_in2)
	{
		if (redir->file_in2)
			free_cmd2(redir->file_in2);
	}
	if (redir->dir_out2)
	{
		if (redir->file_out2)
			free_cmd2(redir->file_out2);
	}
	free (redir);
}

void free_pars(t_pars	*pars)
{
	if (pars->all_token)
		free_cmd2(pars->all_token);
	if (pars->all_token)
		free_cmd2(pars->arg);
	if (pars->cmd)
		free(pars->all_token);
	if (pars->redir)
		free_redir(pars->redir);
}

void free_all(t_cmd *cmd)
{
	if (cmd->sav)
	{
		free(cmd->sav->line);
		if (cmd->sav->split_pipe)
			free_cmd2(cmd->sav->split_pipe);
		free(cmd->sav);
	}
	if (cmd->all)
	{
		while (cmd->all->next != NULL)
		{
			if (cmd->all)
				free_pars(cmd->all);
			cmd->all = cmd->all->next;
		}
		free (cmd->all);
	}
	free (cmd);
}
