/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:03:51 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/22 03:42:07 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmd2(char **dest)
{
	int	i;

	i = 0;
	if (!dest)
		return ;
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
	if (!redir)
		return ;
	if (redir->file_in)
		free_cmd2(redir->file_in);
	if (redir->file_out)
		free_cmd2(redir->file_out);
	if (redir->file_in2)
		free_cmd2(redir->file_in2);
	if (redir->file_out2)
		free_cmd2(redir->file_out2);
	if (redir->heredoc_files)
		free_cmd2(redir->heredoc_files);
	free (redir);
}

void	free_pars(t_pars	*pars)
{
	if (pars->all_token)
		free_cmd2(pars->all_token);
	if (pars->arg)
		free_cmd2(pars->arg);
	if (pars->cmd)
		free(pars->cmd);
	if (pars->redir)
		free_redir(pars->redir);
}

void	free_all(t_cmd *cmd)
{
	t_pars	*tmp;

	if (!cmd)
		return ;
	if (cmd->sav)
	{
		free_global(cmd->sav);
		cmd->sav = NULL;
	}
	if (cmd->all)
	{
		while (cmd->all)
		{
			tmp = cmd->all->next;
			free_pars(cmd->all);
			free(cmd->all);
			cmd->all = tmp;
		}
	}
	if (cmd->env)
		ft_free_split(cmd->env);
	free(cmd);
}

void	free_global(t_global *global)
{
    if (!global)
        return ;
    if (global->split_pipe)
        free_cmd2(global->split_pipe);
    free(global);
}
