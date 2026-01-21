/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:05:56 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/20 16:53:43 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_is_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0
		|| ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (1);
	return (0);
}

int	count_token(char *str)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (str[i])
		{
			count++;
			len = len_token(&str[i]);
			i += len;
		}
	}
	return (count);
}
