/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:18:37 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/27 18:20:45 by nyrakoto         ###   ########.fr       */
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

char	*ft_make_path(t_pars *pars, t_cmd *cmd)
{
	int		i;
	char	**paths;
	char	*all;

	i = 0;
	if (!pars || !pars->cmd)
		return (NULL);
	if (access(pars->cmd, X_OK) == 0)
	{
		return (ft_strdup(pars->cmd));
	}
	while (cmd->env[i] && ft_strncmp(cmd->env[i], "PATH=", 5))
		i++;
	if (!cmd->env[i])
		return (NULL);
	paths = ft_split(cmd->env[i] + 5, ':');
	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		all = ft_strjoin3(paths[i], "/", pars->cmd);
		if (access(all, X_OK) == 0)
		{
			ft_free_split(paths);
			return (all);
		}
		free(all);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_split(paths);
	return (NULL);
}
