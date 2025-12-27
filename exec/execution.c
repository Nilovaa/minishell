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

#include "../LIBFT/libft.h"
#include "../pars/parssing.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_exec_simple(t_pars *pars, char **envp)
{
	pid_t	pid;
	char *path = ft_make_path(pars, envp);
	char	**argv;

	if (!pars || !pars->cmd)
		return ;
	if (!path)
		return ;
	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork")	;
		return ;
	}
	if (pid == 0)						//enfant
	{
		execve(path, argv, envp);
		perror("execve");
		exit (1);
	}
	else
		waitpid(pid, NULL, 0);				//parent
	free(path);
	free(argv);
}
