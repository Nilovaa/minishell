/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:16:47 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/27 18:20:44 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	pid_t	pid;
	char *path = ft_make_path(pars, cmd);
	char	**argv;
	int		status;

	if (!pars || !pars->cmd)
		return ;
	if (!path)
	{
		pars->return_value = 127;     // cmd not found
		return ;
	}
	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		pars->return_value = 1;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork")	;
		pars->return_value = 1;
		free(path);
		ft_free_split(argv);
		return ;
	}
	if (pid == 0)						//enfant
	{
		execve(path, argv, cmd->env);
		perror("execve");
		exit (1);
	}
	else
	{
		waitpid(pid, &status, 0);				//parent
		if (WIFEXITED(status))              // return 1 si enfant termine normalement
			pars->return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))       // return d'un signal
			pars->return_value = 128 + WTERMSIG(status);
	}
	free(path);
	free(argv);
}
