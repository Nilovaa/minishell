/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:37:55 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 13:00:30 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"
#include <stdio.h>

char *cpy_token(char *str, char *dest)
{
	int  i;

	i = 0;
	while (i < len_token(str) && str[i])
	{
		// if (str[i] == 39)
		// {
		// 	i++;
		// 	while (str[i] && str[i] != 39)
		// 	{
		// 		dest[i] = str[i];
		// 		i++;
		// 	}
		// 	i++;
		// }
		// else if (str[i] == '"')
		// {
		// 	i++;
		// 	while (str[i] && str[i] != '"')
		// 	{
		// 		dest[i] = str[i];
		// 		i++;
		// 	}
		// 	i++;
		// }
		// else
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int len_token(char *str)
{
	int i;
	
	i = 0;
	if (ft_is_space(str[i]))
		i += skip_space(&str[i]);
	else if (str[i] == 39 || str[i] == '"')
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
				return(i);
		}
	}
	while (str[i] && !ft_is_space(str[i]))
		i++;
	return (i);
}

int ft_is_space(char c)
{
	if ((c > 9 && c < 13)  || c == 32)
		return (1);
	return (0);
}

int skip_space(char *str)
{
	int  i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			break ;
		i++;
	}
	return (i);
}

int count_token(char *str)
{
	int count;
	int i;

	i = 0;
	count = 0;
	if (!ft_is_space(str[i]))
		count++ ;
	while (str[i])
	{
		if (ft_is_space(str[i]) && str[i + 1] == '"')
		{
			count++;
			i += skip_2cot(&str[i]);
		}
		else if (ft_is_space(str[i]) && str[i + 1] == 39)
		{
			count++;
			i += skip_2cot(&str[i]);
		}
		else if (ft_is_space(str[i]) && !ft_is_space(str[i + 1]) && str[i + 1 ] != '\0' )
			count++;
		i++;
	}
	return (count);
}

int check_qote(char *str)
{
	int	i;
	int	cot1;
	int	cot2;

	i = 0;
	cot1 = 0;
	cot2 = 0;
	while (str[i])
	{
		if (str[i] == 39)
			cot1++;
		else if (str[i] == '"')
		 	cot2++;
		i++;
	}
	if (cot1%2 != 0 || cot2%2 != 0)
		return (1);
	return (0);
}

char **split_token(char *str)
{
	char	**dest;

	if (check_qote(str))
		return (NULL);
	// printf("\nle nombre de token == %d\n\n", count_token(str))
	dest = ft_calloc(sizeof(char *), count_token(str) + 1);
	if (!dest)
		return (NULL);
	dest = split_token_utils(str, dest);
	return (dest);
}

char **split_token_utils(char *str, char **dest)
{
	int i;
	int j;
	int tmp;

	i = 0;
	j = 0;
	while (j < count_token(str))
	{
		if (ft_is_space(str[i]))
			i += skip_space(str);
		dest[j] = ft_calloc(sizeof(char), len_token(&str[i]));
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
