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

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_cmd	*cmd_base;

	(void)ac;
	(void)av;
	cmd_base = cmd_init(NULL, env, 0);
	if (!cmd_base)
		return (1);
	ft_signal_interactive();
	while (1)
	{
		line = readline("minishell$ ");
		if (g_signal_received)
		{
			cmd_base->last_exit_status = g_signal_received;
			g_signal_received = 0;
		}
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			cmd = cmd_init(line, cmd_base->env, cmd_base->last_exit_status);
			if (cmd && cmd->all && cmd->all->cmd)
			{
				cmd->all->return_value = cmd_base->last_exit_status;
				ft_check_builtins(cmd->all, cmd);
				cmd_base->last_exit_status = cmd->all->return_value;
				if (cmd->all->global && cmd->all->global->exit)
				{
					int exit_code = cmd->all->return_value;
					ft_free_split(cmd_base->env);
					cmd_base->env = NULL;
					free_all(cmd);
					rl_clear_history();
					free_all(cmd_base);
					return (exit_code);
				}
				ft_free_split(cmd_base->env);
				cmd_base->env = cmd->env;
				cmd->env = NULL;
			}
			free_all(cmd);
		}
		free(line);
	}
	rl_clear_history();
	free_all(cmd_base);
	return (0);
}
