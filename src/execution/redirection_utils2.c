/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:57:46 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/22 19:45:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_build_heredoc_name(char *pid_str, char *num)
{
	char	*tmp;
	char	*file;

	tmp = ft_strjoin3("/tmp/.heredoc_", pid_str, "_");
	if (!tmp)
		return (NULL);
	file = ft_strjoin(tmp, num);
	free(tmp);
	return (file);
}

int	ft_create_heredoc(char *delim, char *tmp_file)
{
	int		fd;

	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	ft_read_file(delim, fd);
	close(fd);
	return (0);
}

int	ft_process_heredocs(t_dir *redir)
{
	int		i;
	char	*tmp_file;

	if (!redir || !redir->file_in2)
		return (0);
	i = 0;
	while (redir->file_in2[i])
	{
		tmp_file = ft_tmp_heredoc();
		if (!tmp_file)
			return (-1);
		if (ft_create_heredoc(redir->file_in2[i], tmp_file) < 0)
		{
			free(tmp_file);
			return (-1);
		}
		redir->heredoc_files = join_redir(tmp_file, redir->heredoc_files);
		free(tmp_file);
		if (!redir->heredoc_files)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_cleanup_heredocs(t_dir *redir)
{
	int	i;

	if (!redir || !redir->heredoc_files)
		return ;
	i = 0;
	while (redir->heredoc_files[i])
	{
		unlink(redir->heredoc_files[i]);
		i++;
	}
}

void	ft_cleanup_and_exit_redir(t_cmd *cmd, char *file, int is_child)
{
	perror(file);
	(void)cmd;
	(void)is_child;
}
