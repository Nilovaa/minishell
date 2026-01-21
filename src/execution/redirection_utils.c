/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:58:26 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 22:05:47 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
