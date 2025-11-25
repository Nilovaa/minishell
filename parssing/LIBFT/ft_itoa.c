/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:41:19 by andriamr          #+#    #+#             */
/*   Updated: 2025/07/14 15:41:38 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_number(int n)
{
	int			i;
	int long	nbr;

	i = 0;
	nbr = (int long)n;
	if (n == 0)
		return (1);
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	while (nbr >= 1)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static char	*nb_zero(char *dest)
{
	dest[0] = '0';
	return (dest);
}

static char	*nb_toa(int long nbr, char *dest, int i)
{
	while (count_number(nbr) > 0 && i >= 1)
	{
		dest[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			i;
	int long	nbr;

	i = count_number(n) - 1;
	nbr = (int long)n;
	dest = ft_calloc(sizeof(char), (count_number(nbr) + 1));
	if (!dest)
		return (NULL);
	if (nbr == 0)
		return (nb_zero(dest));
	if (nbr < 0)
	{
		nbr = -nbr;
		dest[0] = '-';
		return (nb_toa(nbr, dest, i));
	}
	while (count_number(nbr) > 0 && i >= 0)
	{
		dest[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	return (dest);
}
