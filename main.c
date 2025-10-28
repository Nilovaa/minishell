/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:51:21 by andriamr          #+#    #+#             */
/*   Updated: 2025/09/10 18:42:41 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "pipex.h"

char	*cmd_utils(char *cmd)
{
	int 	i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (cmd[0] != '/')
		return (cmd);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			j = i;	
		i++;
	}
	new = ft_strdup(&cmd[j]);
	return (new);
}

char	*path_utils(char *path, char *av)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	if (av[0] != '/')
		return (ft_strdup(ft_strdup(path)));
	while (av[i])
	{
		if (av[i] == '/')
			j = i;	
		i++;
	}
	i = 0;
	while (i < j)
	{
		str[i] = av[i];
		i++;
	}
	str[i] = '\0';
	return (ft_strdup(str));
}

void	child_process(char **file, int *pipe_fd, char **path, char **av)
{
	int		fd;
	char	*path0;
	char	**cmd0;

	fd = open(file[0], O_RDONLY);
	if (fd < 0)
	{
		perror("file1");
		exit (1);
	}
	
	cmd0 = ft_split(cmd_utils(av[2]), ' ');
	path0 = ft_strdup(path[0]);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close (fd);
	close (pipe_fd[0]);
	close (pipe_fd[1]);
	free_two(path);
	free_two(file);
	execve(path0, cmd0, NULL);
	perror("comande error");
	free_two(cmd0);
	free (path0);
}

void	process_p(char **files, int *pipe_fd, char **path, char **av)
{
	int		fd;
	char	**cmd;
	char	*path1;

	fd = open(files[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("file2 error");
		free_two(path);
		free_two(files);
		exit (1);
	}
	cmd = ft_split(av[3], ' ');
	path1 = ft_strdup(path[1]);
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free_two(path);
	free_two(files);
	execve(path1, cmd, NULL);
	perror("comande error");
	free(path1);
	free(cmd);
}

int	main(int ac, char **av, const char **env)
{
	int		pipe_fd[2];
	char	**path;
	char	***cmd;
	char	**files;
	pid_t	pid;

	if (ac != 5)
		return (perror("argv error"), 0);
	cmd = take_cmd(av);
	if (check_commande(cmd, env))
		return (free_three(cmd), perror("commande error"), 0);
	path = take_path(cmd, env);
	files = take_files(av);
	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		return (perror("fork error "), 0);
	else if (pid > 0)
	{
		child_process(files, pipe_fd, path, av);
		exit (1);
	}
	waitpid(pid, NULL, 0);
	process_p(files, pipe_fd, path, av);
	return (0);
}
