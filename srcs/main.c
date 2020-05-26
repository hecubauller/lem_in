/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:27:16 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/24 02:22:40 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_lem			l;

	ft_bzero((void *)&l, sizeof(t_lem));
	if (!read_check_create_graph(&l) || !find_best_flow(&l) || !print(&l))
	{
		free_all(&l);
		write(1, "ERROR\n", 6);
		return (0);
	}
	free_all(&l);
	return (0);
}
