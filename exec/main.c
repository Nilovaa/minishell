/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/23 04:24:59 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../LIBFT/libft.h"
#include "../pars/parssing.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	**ft_make_args(t_pars *pars)			//manambotra anle pars.args ho ilaina amle execve
{
	int i = 0;
	int len = 0;
	char **argv;

	while (pars->arg && pars->arg[len])	
		len++;
	argv = malloc(sizeof(char *) * (len + 2));
	if (!argv)
		return (NULL);
	argv[0] = pars->cmd;
	while (i < len)
	{
		argv[i + 1] = pars->arg[i];
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);							//exec(path, argv, NULL) => args: "cmd, arg0, arg1, arg2, ... , NULL"
}

char *ft_make_path(t_pars *pars, char **envp)  // mitady anle path ao anaty env
{
	int i = 0;
	char **paths;
	char *all;

	if (!pars || !pars->cmd)
		return (NULL);
	if (access(pars->cmd, X_OK) == 0)		//verifiena rah efa chemin
	{
		return (ft_strdup(pars->cmd));
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		all = ft_strjoin3(paths[i], "/", pars->cmd);		//creation anle chemin anle path
		if (access(all, X_OK) == 0)
		{
			ft_free_split(paths);
			return (all);
		}
		free(all);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	ft_exec_simple(t_pars *pars, char **envp)
{
	pid_t	pid;
	char *path = ft_make_path(pars, envp);
	char	**argv;

	if (!pars || !pars->cmd)
		return ;
	if (!path)
		return ;
	argv = ft_make_args(pars);
	if (!argv)
	{
		free(path);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork")	;
		return ;
	}
	if (pid == 0)						//enfant
	{
		execve(path, argv, envp);
		perror("execve");
		exit (1);
	}
	else
		waitpid(pid, NULL, 0);				//parent
	free(path);
	free(argv);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char *line;
	t_pars pars;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)					//ctrl + d
			exit(0);
		if (line[0] != '\0')				//up and down
		{
			add_history(line);
			ft_bzero(&pars, sizeof(t_pars));
			//parsing
			pars.cmd = "ls";
			pars.arg = (char *[]){"-la", NULL};
			pars.global = NULL;
			ft_exec_simple(&pars, envp);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}


