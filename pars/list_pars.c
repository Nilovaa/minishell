/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:51:33 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/18 12:34:11 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

void	add_list_last(t_pars *pars, char *split_pipe)
{
	t_pars	*last;
	t_pars	*first;

	last = init_token(split_pipe);
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

t_pars	*init_token1(t_cmd *cmd)
{
	t_pars	*pars;
	t_pars	*tmp;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	pars->count_token = count_token(cmd->sav->split_pipe[0]);
	pars->global = cmd->all->global;
	pars->all_token = split_token(cmd->sav->split_pipe[0]);
	if (!pars->all_token)
		return (NULL);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = pars->all_token[0];
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	if (!pars->arg)
		return (NULL);
	pars->next = NULL;
	return (pars);
}

static void	add_redir(t_dir *redir, char **all_token)
{
	int	i;
	int	in;
	int	out;
	int	in2;
	int	out2;

	in = 0;
	out = 0;
	in2 = 0;
	out2 = 0;
	i = 0;
	while (all_token[i])
	{
		if (ft_strncmp(all_token[i], ">>", 2) == 0)
			redir->file_out2 = join_redir(all_token[i + 1], redir->file_out2);
		else if (ft_strncmp(all_token[i], "<<", 2) == 0)
			redir->file_in2 = join_redir(all_token[i + 1], redir->file_in2);
		else if (ft_strncmp(all_token[i], "<", 1) == 0)
			redir->file_in = join_redir(all_token[i + 1], redir->file_in);
		else if (ft_strncmp(all_token[i], ">", 1) == 0)
			redir->file_out = join_redir(all_token[i + 1], redir->file_out);
		i++;
	}
}

t_dir	*init_redir(char **all_token)
{
	t_dir	*redir;

	redir = malloc(sizeof(t_dir));
	if (!redir)
		return (NULL);
	add_redir(redir, all_token);
	return (redir);
}

t_pars	*init_token(char *split_pipe)
{
	t_pars	*pars;
	t_pars	*tmp;

	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	pars->count_token = count_token(split_pipe);
	pars->all_token = split_token(split_pipe);
	if (!pars->all_token)
		return (NULL);
	pars->redir = init_redir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = pars->all_token[0];
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	
	if (!pars->arg)
		return (NULL);
	pars->next = NULL;
	return (pars);
}

char	**join_redir(char *file, char **redir)
{
	char	**tmp;
	int		len;
	int		i;

	len = 0;
	if (redir)
	{
		while (redir[len])
			len++;
	}
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	if (!redir)
	{
		tmp[0] = ft_strdup(file);
		tmp[1] = NULL;
		return (tmp);
	}
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(redir[i]);
		i++;
	}
	tmp[i] = ft_strdup(file);
	tmp[i + 1] = NULL;
	free_cmd2(redir);
	return (tmp);
}
