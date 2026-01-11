/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:48:44 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/11 15:12:51 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_tmp_heredoc(void)
{
	static int	i = 0;
	char		*num;
	char		*file;

	num = ft_itoa(i);
	i++;
	if (!num)
		return (NULL);
	file = ft_strjoin3("/tmp/.heredoc_", num, "");
	free(num);
	return (file);
}

/*
** Lit les lignes depuis stdin jusqu'au délimiteur
** FIX: Comparaison correcte du délimiteur (sans le +1)
*/
int	ft_read_file(char *delim, int fd)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delim);
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
	return (0);
}

/*
** Gère le heredoc: crée un fichier temporaire, lit les lignes,
** puis retourne un fd ouvert en lecture
** FIX: Retourne -1 en cas d'erreur (pas 1)
*/
int	ft_take_heredoc(char *delim)
{
	char	*tmp_file;
	int		fd;
	int		fd_read;

	tmp_file = ft_tmp_heredoc();
	if (!tmp_file)
		return (-1);
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

/*
** Applique toutes les redirections pour la commande
** FIX: Retourne -1 en cas d'erreur (cohérent)
*/
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