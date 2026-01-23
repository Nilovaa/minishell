/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:33:07 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/03/10 13:34:43 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;
	int		null;

	null = 0;
	str = (char *)s;
	i = 0;
	if (!s)
		return ;
	while (n != 0)
	{
		str[i] = null;
		i++;
		n--;
	}
}
