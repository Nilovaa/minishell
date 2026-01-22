/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:48:44 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/22 19:38:33 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_redirect_input_files(t_dir *redir, t_cmd *cmd, int is_child)
{
	int	i;
	int	fd;

	i = 0;
	if (redir->file_in)
	{
		while (redir->file_in[i])
		{
			fd = open(redir->file_in[i], O_RDONLY);
			if (fd < 0)
			{
				ft_cleanup_and_exit_redir(cmd, redir->file_in[i], is_child);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_heredocs(t_dir *redir, t_cmd *cmd, int is_child)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	if (redir->heredoc_files)
	{
		while (redir->heredoc_files[i])
		{
			fd = open(redir->heredoc_files[i], O_RDONLY);
			if (fd < 0)
			{
				tmp = redir->heredoc_files[i];
				ft_cleanup_and_exit_redir(cmd, tmp, is_child);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_output_files(t_dir *redir, t_cmd *cmd, int is_child)
{
	int	i;
	int	fd;

	i = 0;
	if (redir->file_out)
	{
		while (redir->file_out[i])
		{
			fd = open(redir->file_out[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				ft_cleanup_and_exit_redir(cmd, redir->file_out[i], is_child);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_append_files(t_dir *redir, t_cmd *cmd, int is_child)
{
	int	i;
	int	fd;

	i = 0;
	if (redir->file_out2)
	{
		while (redir->file_out2[i])
		{
			fd = open(redir->file_out2[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				ft_cleanup_and_exit_redir(cmd, redir->file_out2[i], is_child);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

int	ft_redirection(t_dir *redir, t_cmd *cmd, int is_child)
{
	if (!redir)
		return (0);
	if (ft_redirect_input_files(redir, cmd, is_child) < 0)
		return (-1);
	if (ft_redirect_heredocs(redir, cmd, is_child) < 0)
		return (-1);
	if (ft_redirect_output_files(redir, cmd, is_child) < 0)
		return (-1);
	if (ft_redirect_append_files(redir, cmd, is_child) < 0)
		return (-1);
	return (0);
}
