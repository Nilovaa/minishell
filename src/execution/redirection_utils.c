/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:58:26 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 04:23:59 by andriamr         ###   ########.fr       */
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

static void	ft_heredoc_child(char *delim, int fd, t_cmd *cmd, char *tmp_file)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delim);
	if (cmd)
	{
		if (cmd->cmd_base)
			free_all(cmd->cmd_base);
		free_all(cmd);
	}
	free(tmp_file);
	ft_signal_heredoc();
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
	close(fd);
	rl_clear_history();
	_exit(0);
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
