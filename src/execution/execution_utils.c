/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:26:38 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 22:06:09 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_simple(t_pars *pars, t_cmd *cmd)
{
	char	*path;
	char	**argv;
	pid_t	pid;

	if (!pars || !pars->cmd)
		return ;
	path = ft_get_path(pars, cmd);
	if (!path)
	{
		ft_cleanup_heredocs(pars->redir);
		return ;
	}
	argv = ft_get_argv(pars, path);
	if (!argv)
	{
		free(path);
		ft_cleanup_heredocs(pars->redir);
		return ;
	}
	if (ft_handle_heredoc(pars, path, argv) < 0)
		return ;
	pid = ft_exec(path, argv, pars, cmd);
	if (pid == -1)
		return ;
	ft_parent_wait(pid, pars, path, argv);
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
