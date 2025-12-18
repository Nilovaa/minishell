/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:46:43 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/18 14:47:51 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int	main(int ac, char **av)
{
	if (ac != 1)
		return (ft_putstr_fd("ERROR AC\n", 2), 0);
	if (!ft_strncmp(av[0], "minishell", 9))
		return (ft_putstr_fd("ERROR ARG\n", 2), 0);
	parsing();
	return (0);
}
