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

char	*ft_tmp_heredoc(void)
{
	static int	i = 0;
	char		*num;
	char		*file;
	char		*pid_str;
	char		*tmp;
	int			pid;

	pid = getpid();
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (NULL);
	num = ft_itoa(i);
	i++;
	if (!num)
	{
		free(pid_str);
		return (NULL);
	}
	tmp = ft_strjoin3("/tmp/.heredoc_", pid_str, "_");
	if (!tmp)
	{
		free(pid_str);
		free(num);
		return (NULL);
	}
	file = ft_strjoin(tmp, num);
	free(tmp);
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

int	ft_take_heredoc(char *delim)
{
	char	*tmp_file;
	int		fd;
	int		fd_read;

	tmp_file = ft_tmp_heredoc();
	if (!tmp_file)
		return (-1);
	if (ft_check_existing_heredoc(tmp_file))
	{
		fd_read = open(tmp_file, O_RDONLY);
		free(tmp_file);
		return (fd_read);
	}
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(tmp_file);
		return (-1);
	}
	ft_read_file(delim, fd);
	close(fd);
	fd_read = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(tmp_file);
	return (fd_read);
}

int	ft_redirection(t_dir *redir)
{
	int	i;
	int	fd;

	if (!redir)
		return (0);
	i = 0;
	if (redir->file_in)
	{
		while (redir->file_in[i])
		{
			fd = open(redir->file_in[i], O_RDONLY);
			if (fd < 0)
			{
				perror(redir->file_in[i]);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	i = 0;
	if (redir->file_in2)
	{
		while (redir->file_in2[i])
		{
			fd = ft_take_heredoc(redir->file_in2[i]);
			if (fd < 0)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	i = 0;
	if (redir->file_out)
	{
		while (redir->file_out[i])
		{
			fd = open(redir->file_out[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->file_out[i]);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	i = 0;
	if (redir->file_out2)
	{
		while (redir->file_out2[i])
		{
			fd = open(redir->file_out2[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->file_out2[i]);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}
