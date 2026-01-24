/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/24 18:14:25 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_handle_exit_builtin(t_cmd *cmd_base, t_cmd *cmd)
{
	int	exit_code;

	if (!cmd || !cmd->all || !cmd->all->global)
		return (-1);
	if (!cmd->all->global->exit)
		return (-1);
	exit_code = cmd->all->return_value;
	if (cmd_base && cmd_base->env)
	{
		ft_free_split(cmd_base->env);
		cmd_base->env = NULL;
	}
	free_all(cmd);
	rl_clear_history();
	free_all(cmd_base);
	return (exit_code);
}

static int	ft_process_command(t_cmd *cmd, t_cmd *cmd_base)
{
	int	exit_code;

	if (!cmd)
	{
		cmd_base->last_exit_status = 2;
		return (-2);
	}
	if (cmd->all)
	{
		cmd->all->return_value = cmd_base->last_exit_status;
		ft_check_builtins(cmd->all, cmd);
		cmd_base->last_exit_status = cmd->all->return_value;
		exit_code = ft_handle_exit_builtin(cmd_base, cmd);
		if (exit_code != -1)
			return (exit_code);
		ft_free_split(cmd_base->env);
		cmd_base->env = cmd->env;
		cmd->env = NULL;
	}
	else
		cmd_base->last_exit_status = 2;
	free_all(cmd);
	return (-2);
}

static int	return_result(t_cmd *cmd_base, char *line)
{
	int		rc;
	t_cmd	*cmd;

	add_history(line);
	cmd = cmd_init(line, cmd_base->env, cmd_base->last_exit_status);
	if (cmd)
		cmd->cmd_base = cmd_base;
	rc = ft_process_command(cmd, cmd_base);
	free(line);
	if (rc >= 0)
		return (rc);
	return (-1);
}

static int	ft_handle_readline_result(char *line, t_cmd *cmd_base)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		free_all(cmd_base);
		return (0);
	}
	if (ft_is_only_spaces(line))
	{
		free(line);
		cmd_base->last_exit_status = 0;
		return (-1);
	}
	if (line[0] != '\0')
		return (return_result(cmd_base, line));
	return (free (line), -1);
}

static int	ft_main_loop(t_cmd *cmd_base)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("minishell$ ");
		ft_update_signal_status(cmd_base);
		result = ft_handle_readline_result(line, cmd_base);
		if (result != -1)
			return (result);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd_base;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	cmd_base = ft_init_cmd_base(env);
	if (!cmd_base)
		return (1);
	ft_signal_interactive();
	return (ft_main_loop(cmd_base));
}
