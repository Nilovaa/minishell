/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/05 10:42:40 by nyrakoto         ###   ########.fr       */
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
	t_cmd *cmd;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)					//ctrl + d
			exit(0);
		cmd = cmd_init(line);
		if (line[0] != '\0')				//up and down
		{
			add_history(line);
			ft_check_builtins(cmd->all, envp);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}

