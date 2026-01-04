/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/27 18:23:34 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char *line;
	t_pars pars1;
	t_pars pars2;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)					//ctrl + d
			exit(0);
		if (line[0] != '\0')				//up and down
		{
			add_history(line);
			ft_bzero(&pars1, sizeof(t_pars));
			ft_bzero(&pars2, sizeof(t_pars));
			//parsing
			pars1.cmd = "ls";
   			pars1.arg = (char *[]){"-l", NULL};
 			pars1.next = &pars2;

			pars2.cmd = "grep";
			pars2.arg = (char *[]){"main", NULL};
			pars2.next = NULL;
			ft_exec_simple_pipe(&pars1, envp);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}

