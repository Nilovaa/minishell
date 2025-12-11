/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:46:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 14:00:35 by andriamr         ###   ########.fr       */
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
	int			i;
	int			j;
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
		{
			j = 0;
			while (cmd->all != NULL)
			{
				i = 0;
				if (cmd->all)
				{					
					printf("PART %d\n", j+1);
					printf("all token == {");
					while (cmd->all->all_token[i])
					{
						printf(" %s,", cmd->all->all_token[i]);
						i++;
					}
					printf("...}\n");
					i = 0;
					printf("commande == %s\n", cmd->all->cmd);
					if (cmd->all->arg)
					{
						printf("argument == {");
						while (cmd->all->arg[i])
						{
							printf("%s ,", cmd->all->arg[i]);
							i++;
						}
						printf("...}\n");
					}
				}
				j++;
				cmd->all = cmd->all->next;
			}
		}
		free(line);
		line = NULL;
		printf("\033[1;31mminishell$\033[0m ==>");  
	}
}

int	main(void)
{
	parsing();
	return (0);
}
