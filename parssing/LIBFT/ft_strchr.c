/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:56:56 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/18 12:34:02 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	int				i;
	unsigned char	j;

	i = 0;
	j = (unsigned char)c;
	str = (char *)s;
	if (j == '\0')
		return (&(str[ft_strlen(s)]));
	while (str[i])
	{
		if (str[i] == j)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
