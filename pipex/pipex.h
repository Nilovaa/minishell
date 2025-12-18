/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:52:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/09/10 18:42:01 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "LIBFT/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

int		main(int ac, char **av, const char **env);
char	**path(const char **env);
char	**take_path(char ***cmd, const char **env);
char	**take_files(char **av);
char	***take_cmd(char **av);
char	*acces_checker(char **path, const char *cmd);
void	free_two(char **str);
void	free_three(char ***str);
void	free_all(char **path_all, char ***cmd, char **file);
void	ft_print_path(char **path);
void	process_p(char **files, int *pipe_fd, char **path, char **av);
void	child_process(char **file, int *pipe_fd, char **path, char **av);
int		check_commande(char ***cmd, const char **env);
char	*cmd_utils(char *cmd);
char	*path_utils(char *path, char *av);

#endif
