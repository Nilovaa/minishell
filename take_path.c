/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:13 by andriamr          #+#    #+#             */
/*   Updated: 2025/09/10 18:41:39 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	len_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	**path(const char **env)
{
	int		i;
	int		j;
	char	**dest;
	char	**tmp2;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	dest = ft_split(env[i] + 5, ':');
	tmp2 = ft_calloc(sizeof(char *), len_split(dest) + 1);
	if (!tmp2)
		return (NULL);
	j = 0;
	while (dest[j])
	{
		tmp2[j] = ft_strjoin(dest[j], "/");
		j++;
	}
	return (free_two(dest), tmp2);
}

char	**take_path(char ***cmd, const char **env)
{
	char	**path_all;
	char	**tmp3;
	char	**tmp;

	tmp3 = path(env);
	path_all = ft_calloc(sizeof(char *), 3);
	if (!path_all)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), 3);
	tmp[0] = acces_checker(tmp3, cmd[0][0]);
	tmp[1] = acces_checker(tmp3, cmd[1][0]);
	tmp[2] = 0;
	path_all[0] = ft_strjoin(tmp[0], cmd[0][0]);
	path_all[1] = ft_strjoin(tmp[1], cmd[1][0]);
	free_two(tmp3);
	free_three(cmd);
	return (path_all);
}

char	***take_cmd(char **av)
{
	char	***cmd_all;

	cmd_all = ft_calloc(sizeof(char ***), 3);
	if (!cmd_all)
		return (NULL);
	cmd_all[0] = ft_split(av[2], ' ');
	cmd_all[1] = ft_split(av[3], ' ');
	cmd_all[2] = 0;
	return (cmd_all);
}

char	**take_files(char **av)
{
	char	**files;

	files = ft_calloc(sizeof(char *), 3);
	if (!files)
		return (NULL);
	files[0] = ft_strdup(av[1]);
	files[1] = ft_strdup(av[4]);
	files[2] = NULL;
	return (files);
}
