/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:58:26 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 19:46:43 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_make_heredoc_name(int count)
{
	char	*num;
	char	*file;

	num = ft_itoa(count);
	if (!num)
		return (NULL);
	file = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (file);
}

char	*ft_tmp_heredoc(void)
{
	static int	count = 0;
	char		*file;

	file = ft_make_heredoc_name(count);
	while (file && access(file, F_OK) == 0)
	{
		free(file);
		count++;
		file = ft_make_heredoc_name(count);
	}
	count++;
	return (file);
}

static void	ft_clean_child_mem(t_cmd *cmd, char *tmp_file)
{
	if (cmd)
	{
		if (cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
	}
	if (tmp_file)
		free(tmp_file);
}

static void	ft_heredoc_loop(int fd, char *delim, size_t len)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delim, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static void	ft_heredoc_child(char *delim, int fd, t_cmd *cmd, char *tmp_file)
{
	char	delim_buf[PATH_MAX];
	size_t	len;

	ft_strlcpy(delim_buf, delim, PATH_MAX);
	ft_clean_child_mem(cmd, tmp_file);
	len = ft_strlen(delim_buf);
	ft_set_heredoc_fd(fd);
	ft_signal_heredoc();
	ft_heredoc_loop(fd, delim_buf, len);
	close(fd);
	rl_clear_history();
	exit(0);
}

int	ft_read_file(char *delim, int fd, t_cmd *cmd, char *tmp_file)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		close(fd);
		return (-1);
	}
	if (pid == 0)
		ft_heredoc_child(delim, fd, cmd, tmp_file);
	close(fd);
	ft_signal_ignore();
	waitpid(pid, &status, 0);
	ft_signal_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (-1);
	if (WIFSIGNALED(status))
		return (-1);
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
