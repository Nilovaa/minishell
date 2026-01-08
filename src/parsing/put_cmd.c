/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:00:06 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/08 14:03:01 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_char2(char **str)
{
	int	i;

	i = 0;
	printf("{");
	while (str[i])
	{
		printf(" %s,", str[i]);
		i++;
	}
}

void	print_all(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->all)
	{
		printf("\n \033[1;32mPART$\033[0m == %d \n", 1 + i);
		printf("all_toker == {");
		j = 0;
		while (cmd->all->all_token[j])
		{
			printf(" %s,", cmd->all->all_token[j]);
			j++;
		}
		printf("...}\n");
		if (cmd->all->all_token)
			printf("commande == %s\n", cmd->all->cmd);
		else
		 	ft_putstr_fd("NO COMMANDE\n", 2);
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
		if (cmd->all->redir)
			print_redir(cmd->all->redir);
		cmd->all = cmd->all->next;
		i++;
	}
}

void	print_redir(t_dir *redir)
{
	if (redir->file_in)
	{
		printf("IN \n");
		print_cdm2(redir->file_in);
	}
	if (redir->file_in2)
	{
		printf("IN2 \n");
		print_cdm2(redir->file_in2);
	}
	if (redir->file_out)
	{
		printf("OUT \n");
		print_cdm2(redir->file_out);
	}
	if (redir->file_out2)
	{
		printf("OUT2 \n");
		print_cdm2(redir->file_out2);
	}
}

void	print_cdm2(char **str)
{
	int	i;

	i = 0;
	ft_putstr_fd("redir == ", 1);
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putstr_fd(", ", 1);
		i++;
	}
	ft_putstr_fd("...\n", 1);
}
