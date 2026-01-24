/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:32:09 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:33:40 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_child(t_cmd *cmd, char *path, char **argv, int code)
{
	if (path)
		free(path);
	if (argv)
		free(argv);
	if (cmd && cmd->cmd_base)
		free_all(cmd->cmd_base);
	free_all(cmd);
	exit(code);
}

int	ft_check_empty_cmd(t_pars *pars)
{
	if (pars->cmd[0] == '\0')
	{
		ft_putstr_fd("'': command not found\n", 2);
		pars->return_value = 127;
		ft_cleanup_heredocs(pars->redir);
		return (1);
	}
	return (0);
}
