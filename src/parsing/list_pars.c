/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:51:33 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 12:27:40 by andriamr         ###   ########.fr       */
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

int	len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static void	*ft_free_tmp(char **tmp, int len)
{
	while (--len >= 0)
		free(tmp[len]);
	free(tmp);
	return (NULL);
}

static char	**create_first_redir(char *file)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strdup(file);
	if (!tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	tmp[1] = NULL;
	return (tmp);
}

static int	copy_existing_redir(char **tmp, char **redir, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(redir[i]);
		if (!tmp[i])
		{
			ft_free_tmp(tmp, i);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**join_redir(char *file, char **redir)
{
	char	**tmp;
	int		len;

	if (!redir)
		return (create_first_redir(file));
	len = len_split(redir);
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	if (!copy_existing_redir(tmp, redir, len))
		return (NULL);
	tmp[len] = ft_strdup(file);
	if (!tmp[len])
		return (ft_free_tmp(tmp, len));
	tmp[len + 1] = NULL;
	free_cmd2(redir);
	return (tmp);
}
