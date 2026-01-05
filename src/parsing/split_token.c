/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:28:45 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/05 14:34:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_token_utils(char *str, char **dest)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (j < count_token(str))
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		dest[j] = ft_calloc(sizeof(char), len_token(&str[i]) + 1);
		if (!dest[j])
			return (NULL);
		cpy_token(&str[i], dest[j]);
		tmp = len_token(&str[i]);
		i = i + tmp + 1;
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**split_token(char *str)
{
	char	**dest;

	if (check_qote(str))
		return (NULL);
	dest = ft_calloc(sizeof(char *), count_token(str) + 1);
	if (!dest)
		return (NULL);
	dest = split_token_utils(str, dest);
	return (dest);
}

// int	count_token(char *str)
// {
// 	int	count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	if (!ft_is_space(str[i]))
// 		count++ ;
// 	while (str[i])
// 	{
// 		if (ft_is_space(str[i]) && str[i + 1] == '"')
// 		{
// 			count++;
// 			i += skip_2cot(&str[i]);
// 		}
// 		else if (ft_is_space(str[i]) && str[i + 1] == 39)
// 		{
// 			count++;
// 			i += skip_2cot(&str[i]);
// 		}
// 		else if (ft_is_space(str[i]) && !ft_is_space(str[i + 1])
// 			&& str[i + 1] != '\0' )
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int count_token(char *str)
{
	int i = 0;
	int count = 0;

	while (str[i])
	{	
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (!str[i])
			break;
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] == 39)
				i++;
			count++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				i++;
			count++;
		}
		else
		{
			while (str[i] && !ft_is_space(str[i]) && str[i] != 39 && str[i] != '"')
				i++;
			count++;
		}
	}
	return count;

}

int	len_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (str[i] == 39 || str[i] == '"')
	{
		if (str[i] == 39)
		{
			while (str[i] && str[i] != 39)
				i++;
			if (ft_is_space(str[i + 1]))
				return (i);
		}
		else if (str[i] == '"')
		{
			while (str[i] && str[i] != '"')
				i++;
			if (ft_is_space(str[i]))
				return (i);
		}
	}
	while (str[i] && !ft_is_space(str[i]))
		i++;
	return (i);
}

char	*cpy_token(char *str, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len_token(str) && str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				dest[j++] = str[i++];
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				dest[j++] = str[i++];
			i++;
		}
		else
			dest[j++] = str[i];
		i++;
	}
	dest[j++] = '\0';
	return (dest);
}
