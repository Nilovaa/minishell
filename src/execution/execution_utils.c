/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:26:38 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 18:13:14 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 

#include "../../include/minishell.h"

static void	ft_exit_child(t_cmd *cmd, char *path, char **argv, int code)
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

static void	ft_child_simple(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**argv;

	ft_signal_child();
	if (ft_redirection(pars->redir, cmd, 1) < 0)
		ft_exit_child(cmd, NULL, NULL, 1);
	path = ft_make_path(pars, cmd);
	if (!path)
		ft_exit_child(cmd, NULL, NULL, pars->return_value);
	argv = ft_make_args(pars);
	if (!argv)
		ft_exit_child(cmd, path, NULL, 1);
	execve(path, argv, cmd->env);
	perror("execve");
	ft_exit_child(cmd, path, argv, 126);
}

static void	ft_wait_simple(pid_t pid, t_pars *pars)
{
	int	status;

	ft_signal_ignore();
	waitpid(pid, &status, 0);
	ft_signal_interactive();
	ft_cleanup_heredocs(pars->redir);
	if (WIFEXITED(status))
		pars->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		pars->return_value = 128 + WTERMSIG(status);
}

static int	ft_check_empty_cmd(t_pars *pars)
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

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	pid_t	pid;

	if (!pars || !pars->cmd)
		return ;
	if (ft_check_empty_cmd(pars))
		return ;
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
	ft_wait_simple(pid, pars);
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