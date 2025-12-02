/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:46:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/02 12:23:43 by andriamr         ###   ########.fr       */
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
		printf("token%d == \"%s\" \n", i, str[i]);
		i++;
	}

}

// void parsing(void )
// {
// 	char		*line;
// 	char		**cmd;
// 	char		**token;
// 	int			i;
	
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		cmd = split_pipe(line);
// 		if (cmd != NULL)
// 		{
// 			free (line);
// 			i = 0;
// 			while(cmd[i])
// 			{
// 				token = split_token(cmd[i]);
// 				if (!token)
// 					break ;
// 				printf("\n PART %d == %s \n", i + 1, cmd[i]);
// 				print_token(token);
// 				free_cmd2(token);
// 				i++;
// 			}
// 			free_cmd2(cmd);
// 		}
// 		else
// 		{
// 			printf("ERROR cmd\n");
// 			free(line);	
// 		}
// 	}
// }


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
		cmd = cmd_init(line);
		if (cmd != NULL)
		{
			j = 0;
			while (cmd->all[j])
			{
				printf("PART %d\n", j+1);
				i = 0;
				if (cmd->all[j])
				{
					printf("all token == {");
					while (cmd->all[j]->all_token[i])
					{
						printf(" %s,", cmd->all[j]->all_token[i]);
						i++;
					}
					printf("...}\n");

					i = 0;
					printf("commande == %s\n", cmd->all[j]->cmd);
					if (cmd->all[j]->arg)
					{
						printf("argument == {");
						while (cmd->all[j]->arg[i])
						{
							printf("%s ,", cmd->all[j]->arg[i]);
							i++;
						}
						printf("...}\n");
					}
				}
				j++;
			}
		}
		else
			printf("ERROR cmd\n");
		// free(line);	
	}
}

int	main(void)
{
	parsing();
	return (0);
}
