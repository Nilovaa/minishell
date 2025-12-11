/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 08:58:40 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 18:10:06 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int check_double_pipe(int i, char *str)
{
	i++;
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (!str[i])
		return (0);
	else if (str[i] == '|')
		return (0);
	return (1);
}

void space(int i,char *str)
{
	while (str[i] && ft_is_space(str[i]))
		i++;	
}

int check_pipe(char *str)
{
	int i;
	int	last;

	i = 0;
	last = -1;
	space(i, str);
	if (str[i] == '|')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (!check_double_pipe(i, str))
				return (0);
			last = i;
		}
		i++;
	}
	if (last == -1)
		return (1);
	last++;
	space(last, str);
	if (!str[last])
		return (0);
	return (1);
}
