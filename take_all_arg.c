/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:28:13 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/18 13:28:26 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char **take_av(int ac, char **av)
{
	int i;
	char **str;

	i = 0;
	str = malloc(sizeof (char *) * ac);
	if (!str)
		return (NULL);
	while (i < ac - 1)
	{
		str[i] = ft_strdup(av[i + 1]);
		i++;
	}
	str[i] = NULL;
	return (str);
}