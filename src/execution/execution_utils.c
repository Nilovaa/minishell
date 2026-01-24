/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:26:38 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 08:30:00 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_child_simple(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**argv;
	int		exit_code;

	ft_signal_child();
	if (ft_redirection(pars->redir, cmd, 1) < 0)
	{
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	path = ft_make_path(pars, cmd);
	if (!path)
	{
		exit_code = pars->return_value;
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(exit_code);
	}
	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		if (cmd && cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
		exit(1);
	}
	execve(path, argv, cmd->env);
	perror("execve");
	free(path);
	free(argv);
	if (cmd && cmd->cmd_base)
		free_all(cmd->cmd_base);
	free_all(cmd);
	exit(126);
}

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (!pars || !pars->cmd)
		return ;
	if (pars->cmd[0] == '\0')
	{
		ft_putstr_fd("'': command not found\n", 2);
		pars->return_value = 127;
		ft_cleanup_heredocs(pars->redir);
		return ;
	}
	if (ft_process_heredocs(pars->redir, cmd) < 0)
	{
		ft_cleanup_heredocs(pars->redir);
		pars->return_value = 130;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		pars->return_value = 1;
		ft_cleanup_heredocs(pars->redir);
		return ;
	}
	if (pid == 0)
		ft_child_simple(pars, cmd);
	ft_signal_ignore();
	waitpid(pid, &status, 0);
	ft_signal_interactive();
	ft_cleanup_heredocs(pars->redir);
	if (WIFEXITED(status))
		pars->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pars->return_value = 128 + WTERMSIG(status);
}

int	ft_change_to_dir(char *path, t_pars *pars, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		has_cwd;

	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		pars->return_value = 1;
		return (1);
	}
	has_cwd = (getcwd(cwd, PATH_MAX) != NULL);
	if (chdir(path) != 0)
	{
		perror("cd");
		pars->return_value = 1;
		return (1);
	}
	if (has_cwd)
		ft_update_oldpwd(cmd, cwd);
	ft_update_pwd(cmd);
	pars->return_value = 0;
	return (0);
}

char	*ft_get_path(t_pars *pars, t_cmd *cmd)
{
	char	*path;

	path = ft_make_path(pars, cmd);
	if (!path)
		return (NULL);
	return (path);
}
