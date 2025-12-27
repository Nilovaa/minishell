/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:27:45 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/27 18:23:34 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../LIBFT/libft.h"
#include "../pars/parssing.h"

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
			pars.arg = (char *[]){"-al",NULL};
			pars.global = NULL;
			ft_exec_simple(&pars, envp);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}


