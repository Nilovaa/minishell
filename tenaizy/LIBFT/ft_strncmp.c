/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:47:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/03/06 16:21:09 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!s1 && !s2))
		return (0);
	if (!s2)
		return (s1[i]);
	if (!s1)
		return (0 - s2[i]);
	while ((s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] == s2[i]) && ((i + 1) < n))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
