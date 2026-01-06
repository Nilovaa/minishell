/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/05 14:38:42 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <unistd.h>
/*
void printf_test(t_cmd *cmd)
{	
	printf("\n \033[1;32mdebut test$\033[0m \n");
	printf("test global ==\n");
	printf("cmd->global->line = %s\n", cmd->sav->line);
	printf("cmd->global->pipe = %d\n", cmd->sav->pipe);
	printf("split-pipe\n");
	print_cmd(cmd->sav->split_pipe);
	printf("split-pipe\n");
	printf("\ntest pars\n");
	printf("cmd->pars->count_token = %d\n", cmd->all->count_token);
	print_token(cmd->all->all_token);
	printf("cmd->pars->cmd = %s\n", cmd->all->cmd);
	print_cmd(cmd->all->arg);
	printf("\033[1;31mEXEC$\033[0m \n");
}
*/

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	char	*line;
	t_cmd	*cmd;
	t_cmd	*cmd_base;

	cmd_base = cmd_init(NULL, env);
	if (!cmd_base)
		return (1);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			cmd = cmd_init(line, cmd_base->env);
			if (cmd && cmd->all && cmd->all->cmd)
				ft_check_builtins(cmd->all, cmd);
			cmd_base->env = cmd->env;
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}

