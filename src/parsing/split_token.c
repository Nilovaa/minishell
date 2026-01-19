/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:28:45 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/16 15:42:20 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_token_utils(char *str, char **dest)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (str[i] && j < count_token(str))
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (str[i])
		{
			len = len_token(&str[i]);
			dest[j] = ft_calloc(sizeof(char), len + 1);
			if (!dest[j])
				return (NULL);
			cpy_token(&str[i], dest[j]);
			i += len;
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**split_token(char *str)
{
	char	**dest;

	if (check_qote(str))
		return (ft_putstr_fd("Error: Unclosed quote\n", 2), NULL);
	dest = ft_calloc(sizeof(char *), count_token(str) + 1);
	if (!dest)
		return (NULL);
	dest = split_token_utils(str, dest);
	return (dest);
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

// int count_token(char *str)
// {
// 	int i = 0;
// 	int count = 0;

// 	while (str[i])
// 	{	
// 		while (str[i] && ft_is_space(str[i]))
// 			i++;
// 		if (!str[i])
// 			break;
// 		if (ft_is_redir(&str[i]))
// 		{
// 			if (str[i] == '>' && str[i + 1] == '>')
// 				i += 2;
// 			else if (str[i] == '<' && str[i + 1] == '<')
// 				i += 2;
// 			else
// 				i++;
// 			count++;
// 		}
// 		if (str[i] == 39)
// 		{
// 			i++;
// 			while (str[i] && str[i] != 39)
// 				i++;
// 			if (str[i] == 39)
// 				i++;
// 			count++;
// 		}
// 		else if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			if (str[i] == '"')
// 				i++;
// 			count++;
// 		}
// 		else
// 		{
// 			while (str[i] && !ft_is_space(str[i]) && str[i] != 39 && str[i] != '"')
// 				i++;
// 			count++;
// 		}
// 	}
// 	return count;
// }

void	update_quote_state(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

int	len_token(char *str)
{
	int	i;
	int	in_sq;
	int	in_dq;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	if (!in_sq && !in_dq && (str[i] == '<' || str[i] == '>'))
	{
		i++;
		if (str[i] == str[i - 1])
			i++;
		return (i);
	}
	while (str[i])
	{
		update_quote_state(str[i], &in_sq, &in_dq);
		if (!in_sq && !in_dq && (ft_is_space(str[i])
				|| str[i] == '<' || str[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

// int	len_token(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && ft_is_space(str[i]))
// 		i++;
// 	if (str[i] == 39 || str[i] == '"')
// 	{
// 		if (str[i] == 39)
// 		{
// 			while (str[i] && str[i] != 39)
// 				i++;
// 			if (ft_is_space(str[i + 1]))
// 				return (i);
// 		}
// 		else if (str[i] == '"')
// 		{
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			if (ft_is_space(str[i]))
// 				return (i);
// 		}
// 		else if (ft_is_redir(str))
// 		{
// 			if (str[i] == '>' && str[i + 1] == '>')
// 				return (2);
// 			else if (str[i] == '<' && str[i + 1] == '<')
// 				return (2);
// 			else
// 				return (1);
// 		}
// 	}
// 	while (str[i] && !ft_is_space(str[i]))
// 		i++;
// 	return (i);
// }

char	*cpy_token(char *str, char *dest)
{
	int	i;
	int	len;

	i = 0;
	len = len_token(str);
	while (i < len && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
