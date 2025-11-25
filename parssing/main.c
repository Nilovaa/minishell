/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:46:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/25 07:57:06 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("\ntoken%d == \"%s\" \n", i, str[i]);
		i++;
	}

}

int	main(void)
{
	char		*line;
	char		**cmd;
	char		**token;
	int			i;
	// t_pars	*pars;
	while (1)
	{
		line = readline("minishell$ ");
		cmd = split_pipe(line);
		if (cmd != NULL)
		{
			free (line);
			i = 0;
			while(cmd[i])
			{
				token = split_token(cmd[i]);
				printf("\n PART %d == %s \n", i + 1, cmd[i]);
				print_token(token);
				free_cmd2(token);
				i++;
			}
			free_cmd2(cmd);
		}
		else
		{
			printf("ERROR cmd\n");
			free(line);	
		}
	}
	return (0);
}
