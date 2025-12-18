/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:37:55 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/16 17:02:49 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int	ft_is_space(char c)
{
	if ((c > 9 && c < 13) || c == 32)
		return (1);
	return (0);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	check_qote(char *str)
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
	if (cot1 % 2 != 0 || cot2 % 2 != 0)
		return (1);
	return (0);
}
