/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 06:50:32 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/24 12:12:20 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int	skip_1cot(char *str)
{
	int	i;

	i = 1 ;
	// printf ("\nao anaty simple cote\n");
	while (str[i])
	{
		if (str[i] == 39)
		{
			// printf ("\ntapitr eto simple cote\n\n");	
			break ;
		}
		// printf("%c", str[i]);
		i++;
	}
	if (str[i] == '\0')
	{
		printf("\nsimple cote misokatra nefa tsy midy\n");
		return (0);
	}
	return (i);
}

int	skip_2cot(char *str)
{
	int	i;

	i = 1;
	// printf ("\nao anaty duble cote\n");
	while (str[i])
	{
		if (str[i] == '"')
		{
			// printf ("\ntapitr eto duble cote\n\n");
			break ;
		}
		// printf("%c", str[i]);
		i++;
	}
	if (str[i] == '\0')
	{
		return (0);
		// printf("\n\ndouble cote misokatra nefa tsy midy\n");
	}
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
	{
		// printf("\nsimple cote misokatra nefa tsy midy ao @ cat1cot\n");
		return (0);
	}
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
	{
		// printf("\nsimple cote misokatra nefa tsy midy ao @ cat1cot\n");
		return (0);
	}
	dest[k] = src[a];
	a++;
	k++;
	i += a;
	return (a);
}
