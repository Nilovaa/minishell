/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:04:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/24 12:05:55 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < (n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (!src || !dst || !size)
		return (ft_strlen((char *)src));
	if (size == 0)
		return (ft_strlen((char *)src));
	if (size > ft_strlen((char *)src))
	{
		ft_strcpy(dst, (char *)src);
		return (ft_strlen((char *)src));
	}
	else if (size <= ft_strlen((char *)src))
	{
		ft_strncpy(dst, (char *)src, size);
		return (ft_strlen((char *)src));
	}
	ft_strncpy(dst, (char *)src, size);
	return (ft_strlen((char *)src));
}
