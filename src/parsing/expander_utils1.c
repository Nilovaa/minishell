/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:03:22 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:22:07 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_quoted_token(char *token)
{
	int	i;

	if (!token || !*token)
		return (0);
	if (token[0] == '"' || token[0] == '\'')
		return (1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_words_expanded(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if ((str[i] == ' ' || str[i] == '\t') && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}

void	handle_val_utils(char **res, char *val)
{
	char	*tmp;

	tmp = ft_strjoin(*res, val);
	free(*res);
	free(val);
	*res = tmp;
}
