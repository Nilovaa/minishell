/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:01:07 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 13:04:13 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int	ft_count_pipe(char *str)
{
	int	count;
	int	i;
	int tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		tmp = 1;
		if (str[i] == '|')
			count++;
		else if (str[i] == '"')
		{
			tmp = skip_2cot(&str[i]);
			i += tmp;
		}
		else if (str[i] == 39)
		{
			tmp = skip_1cot(&str[i]);
			i += tmp; 		
		}
		i++;
		if (tmp == 0)
			return (0);
	}
	return (count + 1);
}

int	len_sep(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			break ;
		else if (str[i] == '"')
			i += skip_2cot(&str[i]);
		else if (str[i] == 39)
			i += skip_1cot(&str[i]);
		i++;
	}
	return (i);
}
