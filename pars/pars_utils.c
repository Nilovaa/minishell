/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:05:56 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/18 15:42:00 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"
#include <stdlib.h>

void	print_cmd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("\ncmd%d == \"%s\" \n", i, str[i]);
		i++;
	}
}

void	print_token(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("token%d == \"%s\" \n", i, str[i]);
		i++;
	}
}

void	parsing(void )
{
	char		*line;
	t_cmd		*cmd;

	while (1)
	{
		cmd = NULL;
		line = readline("minishell$ ");
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);
			break ;
		}
		else if (!check_pipe(line))
		{
			free(line);
			ft_putstr_fd("SYNTAX ERROR\n", 2);
		}
		cmd = cmd_init(line);
		if (cmd != NULL)
		{
			print_all(cmd);
			free_all(cmd);
		}
		else
			free(line);
		printf("\033[1;31mminishell$\033[0m ==>");
	}
}
