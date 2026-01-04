/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 09:55:27 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/04 09:55:32 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_first_child(t_pars *pars, char **envp, int fd[2])
{
    char *path;
    char **arg;

    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(fd[1]);
    path = ft_make_path(pars, envp);
    arg = ft_make_args(pars);
    if (!path || !arg)
    {
        if (path)
            free(path);
        if (arg)
            ft_free_split(arg);
        exit (127);
    }
    execve(path, arg, envp);
    perror("execve");
    free(path);
    ft_free_split(arg);
    exit (1);
}

void    ft_second_child(t_pars *pars, char **envp, int fd[2])
{
    char *path;
    char **arg;

    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(fd[0]);
    path = ft_make_path(pars, envp);
    arg = ft_make_args(pars);
    if (!path || !arg)
    {
        if (path)
            free(path);
        if (arg)
            ft_free_split(arg);
        exit (127);
    }
    execve(path, arg, envp);
    perror("execve");
    free(path);
    ft_free_split(arg);
    exit (1);
}

void    ft_exec_simple_pipe(t_pars *pars, char **envp)
{
    int fd[2];
    pid_t pid1;
    pid_t pid2;
    int status;

    if (!pars || !pars->next || !pars->cmd || !pars->next->cmd)
    {
        if (pars)
            pars->return_value = 1;
        return ;
    }
    if (pipe(fd) == -1)
    {
        perror("pipe");
        pars->return_value = 1;
        return ;
    }
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        pars->return_value = 1;
        return ;
    }
    if (pid1 == 0)
        ft_first_child(pars, envp, fd);
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        pars->return_value = 1;
        return ;
    }
    if (pid2 == 0)
        ft_second_child(pars->next, envp, fd);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    if (WIFEXITED(status))
        pars->return_value = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        pars->return_value = 128 + WTERMSIG(status);
}