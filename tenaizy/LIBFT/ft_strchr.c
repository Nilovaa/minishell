/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:11:25 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:15 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (s[i] != '\0')
	{
		if (s[i] != (char)c)
			i++;
		else
			return ((char *)&s[i]);
	}
	return (NULL);
}
