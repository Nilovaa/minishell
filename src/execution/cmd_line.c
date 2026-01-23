/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:18:37 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/23 03:00:48 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_make_args(t_pars *pars)
{
	int		i;
	int		len;
	char	**argv;

	i = 0;
	len = 0;
	while (pars->arg && pars->arg[len])
		len++;
	argv = malloc(sizeof(char *) * (len + 2));
	if (!argv)
		return (NULL);
	argv[0] = pars->cmd;
	while (i < len)
	{
		argv[i + 1] = pars->arg[i];
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

static char	**ft_get_paths(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd->env[i] && ft_strncmp(cmd->env[i], "PATH=", 5))
		i++;
	if (!cmd->env[i])
		return (NULL);
	return (ft_split(cmd->env[i] + 5, ':'));
}

static char *ft_find_in_path_utils(char *all, t_pars *pars)
{
	if (access(all, X_OK) == 0)
		return (all);
	free(all);
	ft_putstr_fd(pars->cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	pars->return_value = 126;
	return (NULL);
} 


static char	*ft_find_in_paths(char **paths, t_pars *pars)
{
	int		i;
	char	*all;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		all = ft_strjoin3(paths[i], "/", pars->cmd);
		if (!all)
		{
			i++;
			continue ;
		}
		if (access(all, F_OK) == 0)
			return (ft_find_in_path_utils(all, pars));
		free(all);
		i++;
	}
	ft_putstr_fd(pars->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	pars->return_value = 127;
	return (NULL);
}

char	*ft_make_path(t_pars *pars, t_cmd *cmd)
{
	char	**paths;
	char	*res;

	if (!pars || !pars->cmd)
		return (NULL);
	if (access(pars->cmd, F_OK) == 0)
	{
		if (access(pars->cmd, X_OK) == 0)
			return (ft_strdup(pars->cmd));
		ft_putstr_fd(pars->cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		pars->return_value = 126;
		return (NULL);
	}
	paths = ft_get_paths(cmd);
	if (!paths || !paths[0])
	{
		if (paths)
			ft_free_split(paths);
		return (NULL);
	}
	res = ft_find_in_paths(paths, pars);
	ft_free_split(paths);
	return (res);
}
