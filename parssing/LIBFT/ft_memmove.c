/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:09:58 by andriamr          #+#    #+#             */
/*   Updated: 2025/07/14 15:41:59 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	i = 0;
	if (dest <= src)
	{
		ft_memcpy(s1, s2, n);
		return (dest);
	}
	else
	{
		while (i < n)
		{
			s1[n - 1] = s2[n - 1];
			n--;
		}
	}
	return (dest);
}
