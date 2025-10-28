/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:52:25 by andriamr          #+#    #+#             */
/*   Updated: 2025/07/29 23:49:11 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_commande(char ***cmd, const char **env)
{
	char	**all_path;

	if (!cmd[0][0] || !cmd[1][0])
		return (1);
	all_path = path(env);
	if (!acces_checker(all_path, cmd[0][0]) ||
		!acces_checker(all_path, cmd[1][0]))
		return (free_two(all_path), 1);
	return (free_two(all_path), 0);
}

char	*acces_checker(char **path, const char *cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (path[i])
	{
		str = ft_strjoin(path[i], cmd);
		if (access(str, F_OK) == 0)
			return (free(str), path[i]);
		free(str);
		i++;
	}
	return (NULL);
}

void	free_two(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}

void	free_three(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_two(str[i]);
		i++;
	}
	free (str);
}

void	free_all(char **path_all, char ***cmd, char **file)
{
	free_two (file);
	free_two(path_all);
	free_three(cmd);
}
