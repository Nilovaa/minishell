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

char	**ft_make_args(t_pars *pars)			//manambotra anle pars.args ho ilaina amle execve
{
	int i = 0;
	int len = 0;
	char **argv;

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
	return (argv);							//exec(path, argv, NULL) => args: "cmd, arg0, arg1, arg2, ... , NULL"
}

char *ft_make_path(t_pars *pars, char **envp)  // mitady anle path ao anaty env
{
	int i = 0;
	char **paths;
	char *all;

	if (!pars || !pars->cmd)
		return (NULL);
	if (access(pars->cmd, X_OK) == 0)		//verifiena rah efa chemin
	{
		return (ft_strdup(pars->cmd));
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		all = ft_strjoin3(paths[i], "/", pars->cmd);		//creation anle chemin anle path
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
