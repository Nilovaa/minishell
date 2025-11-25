/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:06:32 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/17 18:57:11 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int		nb;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	nb = 0;
	while ((s[i] <= 13 && s[i] >= 9) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = 1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		nb = (nb * 10) + (s[i] - 48);
		i++;
	}
	if (sign == 1)
		nb = -nb;
	return (nb);
}
