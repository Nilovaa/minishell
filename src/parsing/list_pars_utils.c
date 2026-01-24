/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:00:37 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:01:56 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_list_last(t_pars *pars, char *split_pipe, t_cmd *cmd)
{
	t_pars	*last;
	t_pars	*first;

	last = init_token(split_pipe, cmd);
	if (pars == NULL)
	{
		pars = last;
		return ;
	}
	first = pars;
	while (first->next != NULL)
		first = first->next;
	first->next = last;
	last->next = NULL;
}

static void	add_redir(t_dir *redir, char **all_token)
{
	int	i;

	i = 0;
	while (all_token[i])
	{
		if (ft_strncmp(all_token[i], ">>", 2) == 0 && all_token[i + 1])
			redir->file_out2 = join_redir(all_token[i + 1], redir->file_out2);
		else if (ft_strncmp(all_token[i], "<<", 2) == 0 && all_token[i + 1])
			redir->file_in2 = join_redir(all_token[i + 1], redir->file_in2);
		else if (ft_strncmp(all_token[i], "<", 1) == 0 && all_token[i + 1])
			redir->file_in = join_redir(all_token[i + 1], redir->file_in);
		else if (ft_strncmp(all_token[i], ">", 1) == 0 && all_token[i + 1])
			redir->file_out = join_redir(all_token[i + 1], redir->file_out);
		i++;
	}
}

t_dir	*init_redir(char **all_token)
{
	t_dir	*redir;

	redir = ft_calloc(sizeof(t_dir), 1);
	if (!redir)
		return (NULL);
	redir->heredoc_files = NULL;
	add_redir(redir, all_token);
	return (redir);
}
