/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:51:33 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:01:47 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
