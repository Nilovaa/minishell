/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:48:44 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/11 14:37:51 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_build_heredoc_name(char *pid_str, char *num)
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

char	*ft_tmp_heredoc(void)
{
	static int	i;
	char		*num;
	char		*file;
	char		*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	num = ft_itoa(i++);
	if (!num)
		return (free(pid_str), NULL);
	file = ft_build_heredoc_name(pid_str, num);
	free(pid_str);
	free(num);
	return (file);
}

int	ft_read_file(char *delim, int fd)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delim);
	ft_signal_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("heredoc error line\n", 2);
			break ;
		}
		if (ft_strncmp(line, delim, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	ft_signal_interactive();
	return (0);
}

int	ft_check_existing_heredoc(char *tmp_file)
{
	int	fd;

	if (access(tmp_file, F_OK) == 0)
	{
		fd = open(tmp_file, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			return (1);
		}
	}
	return (0);
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

static int	ft_redirect_input_files(t_dir *redir)
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
				return (perror(redir->file_in[i]), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_heredocs(t_dir *redir)
{
	int	i;
	int	fd;

	i = 0;
	if (redir->heredoc_files)
	{
		while (redir->heredoc_files[i])
		{
			fd = open(redir->heredoc_files[i], O_RDONLY);
			if (fd < 0)
				return (perror(redir->heredoc_files[i]), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_output_files(t_dir *redir)
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
				return (perror(redir->file_out[i]), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

static int	ft_redirect_append_files(t_dir *redir)
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
				return (perror(redir->file_out2[i]), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

int	ft_redirection(t_dir *redir)
{
	if (!redir)
		return (0);
	if (ft_redirect_input_files(redir) < 0)
		return (-1);
	if (ft_redirect_heredocs(redir) < 0)
		return (-1);
	if (ft_redirect_output_files(redir) < 0)
		return (-1);
	if (ft_redirect_append_files(redir) < 0)
		return (-1);
	return (0);
}
