/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:00:06 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/16 15:46:41 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"

void print_all(t_cmd *cmd)
{
	int i = 0;
	int j = 0;

	while(cmd->all)
	{
		printf("\nPART  == %d\n", i + 1);
		printf("all_toker == {");
		j = 0;
		while (cmd->all->all_token[j])
		{
			printf(" %s,", cmd->all->all_token[j]);
			j++;
		}
		printf("...}\n");
		printf("commande == %s\n", cmd->all->cmd);
		if (cmd->all->arg)
		{
			printf("argument == {");
			j = 0;
			while (cmd->all->arg[j])
			{
				printf("%s ,", cmd->all->arg[j]);
				j++;
			}
			printf("...}\n");
		}
		print_redir(cmd->all->redir);
		cmd->all = cmd->all->next;
		i++;
	}
}

void print_redir(t_dir *redir)
{
	if (!redir)
		ft_putstr_fd("redir == NONE \n", 1);
	else
	{
		if (redir->file_in)
		{
			printf("\n IN \n");
			print_cdm2(redir->file_in);
		}
		if (redir->file_in2)
		{
			printf("\n IN2 \n");
			print_cdm2(redir->file_in2);
		}
		if (redir->file_out)
		{
			printf("\n OUT \n");
			print_cdm2(redir->file_out);
		}
		if (redir->file_out2)
		{
			printf("\n OUT2 \n");
			print_cdm2(redir->file_out2);
		}
	}
}

void print_cdm2(char **str)
{
	int i;

	i = 0;
	ft_putstr_fd("redir == ", 1);
	while (str[i])
	{
		printf("%d == ", i + 1);
		ft_putstr_fd(str[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

