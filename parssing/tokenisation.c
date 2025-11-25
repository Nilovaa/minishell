/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:37:55 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/25 07:45:24 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"

char *cpy_token(char *str, char *dest)
{
	int  i;

	i = 0;
	// printf("le len_token == %d\n" ,len_token(str));
	while (i < len_token(str) && str[i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			if (str[i] == 39)
			{
				i++;
				while (str[i] && str[i] != 39)
				{
					dest[i] = str[i];
					i++;
				}
			}
			else if (str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
				{
					dest[i] = str[i];
					i++;
				}
			}
		}
		else
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
	{
		i++;
	}
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
			i += skip_2cot(&str[i]);
		else if (ft_is_space(str[i]) && str[i + 1] == 39)
			i += skip_2cot(&str[i]);
		else if (ft_is_space(str[i]) && !ft_is_space(str[i + 1]) && str[i + 1 ] != '\0' )
			count++;
		i++;
	}
	// if (!ft_is_space(str[i]))
		// count++;
	return (count);
}

char **split_token(char *str)
{
	char	**dest;

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
			return (free_cmd2(dest), NULL);
		cpy_token(&str[i], dest[j]);
		tmp = len_token(&str[i]);
		i = i + tmp + 1;
		j++;
	}
	dest[j] = NULL;
	return (dest);
}
