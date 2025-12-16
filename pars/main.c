/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:46:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/16 15:26:54 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"
#include <stdio.h>

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
	int  i;

	i = 0;
	while (str[i])
	{
		printf("token%d == \"%s\" \n", i, str[i]);
		i++;
	}
}

void parsing(void )
{
	char		*line;
	t_cmd		*cmd;
	
	while (1)
	{
		cmd = NULL;
		line = readline("minishell$ ");
		if (!ft_strncmp(line, "exit", 5))
			break;
		else if (!check_pipe(line))
		{
			free(line);
			write (2, "ERROR pipe \n", 12);			
		}			
		cmd = cmd_init(line);			
		if (cmd != NULL)
			print_all(cmd);
		free(line);
		line = NULL;
		free_all(cmd);
		printf("\033[1;31mminishell$\033[0m ==>");  
	}
}

int	main(int ac, char **av)
{
	if (ac != 1)
		return (ft_putstr_fd("ERROR AC\n", 2), 0);
	if (!ft_strncmp(av[0], "minishell", 9))
		return (ft_putstr_fd("ERROR ARG\n", 2), 0);
	parsing();
	return (0);
}
