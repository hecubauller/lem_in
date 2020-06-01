/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
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
