/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:05:14 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/03/06 16:11:10 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	s = (char *)src;
	d = (char *)dest;
	if (!(src))
		return (NULL);
	if (s > d)
		ft_memcpy(dest, src, n);
	else
	{
		while (n != 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (d);
}
