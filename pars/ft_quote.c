/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 06:50:32 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 16:10:49 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int	skip_1cot(char *str)
{
	int	i;

	i = 1 ;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
}

int	skip_2cot(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '"')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
}

int	cat_1cot(char *src, char *dest, int i, int k)
{
	int	a;

	a = 0;
	while (src[a])
	{
		if (src[a] == 39)
			break ;
		dest[k] = src[a];
		a++;
		k++;
	}
	if (src[a] == 0)
		return (0);
	dest[a] = src[a];
	a++;
	k++;
	i += a;
	return (a);
}

int	cat_2cot(char *src, char *dest, int i, int k)
{
	int	a;

	a = 0;
	while (src[a] && src[i] != '"')
	{
		if (src[a] == '"')
			break ;
		dest[k] = src[a];
		a++;
		k++;
	}
	if (src[a] == 0)
		return (0);
	dest[k] = src[a];
	a++;
	k++;
	i += a;
	return (a);
}
