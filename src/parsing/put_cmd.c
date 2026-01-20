/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:00:06 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/20 16:44:28 by andriamr         ###   ########.fr       */
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

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
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
