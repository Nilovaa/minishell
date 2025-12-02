/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:15:14 by andriamr          #+#    #+#             */
/*   Updated: 2025/07/14 15:41:44 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	j;

	j = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (n > i)
	{
		if (str[i] == j)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
