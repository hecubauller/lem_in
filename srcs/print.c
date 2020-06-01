/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_stdin(t_lem *l)
{
	int				i;
	int				j;

	i = -1;
	while (++i < l->stdin_size)
	{
		j = -1;
		while (l->stdin[i][++j])
			;
		write(1, l->stdin[i], j);
		write(1, "\n", 1);
	}
}

static void		assign_ants_for_pathes(t_lem *l, t_solution *s,
										int *ant_per_path)
{
	int				i;
	int				div;
	int				rem;

	div = (l->ant_count + s->path_sum_length) / s->path_count;
	rem = (l->ant_count + s->path_sum_length) % s->path_count;
	i = -1;
	while (++i < s->path_count)
	{
		ant_per_path[i] = div - s->path_length[i] + (rem ? 1 : 0);
		rem ? rem-- : 0;
	}
}

static int		step_forward(t_solution *s, t_room **ant,
								int *ant_per_path, int ant_num)
{
	int				i;
	int				j;

	i = -1;
	while (++i < s->path_count)
	{
		if (ant_per_path[i])
		{
			s->room[i][0]->ant = ant_num;
			ant[ant_num++] = s->room[i][0];
			ant_per_path[i]--;
		}
		j = s->path_length[i];
		while (--j >= 0)
			if (s->room[i][j]->ant > 0)
			{
				s->room[i][j + 1]->ant = s->room[i][j]->ant;
				ant[s->room[i][j]->ant] = s->room[i][j + 1];
				s->room[i][j]->ant = 0;
			}
	}
	return (ant_num);
}

static void		run_ants(t_lem *l, t_solution *s, t_room **ant,
							int *ant_per_path)
{
	int				i;
	int				ant_num;
	char			buff[PRINT_BUFF_SIZE];
	int				buff_i;

	buff_i = 0;
	ant_num = 1;
	i = -1;
	while (++i < s->turn_count)
	{
		ant_num = step_forward(s, ant, ant_per_path, ant_num);
		fast_print(l, ant, buff, &buff_i);
	}
	write(1, buff, buff_i);
}

int				print(t_lem *l)
{
	t_solution		*s;
	t_room			**ant;
	int				*ant_per_path;
	int				i;

	s = l->solution[l->best_solution];
	if (!(ant = (t_room **)malloc((l->ant_count + 1) * PTR_SIZE)))
		return (0);
	i = 0;
	while (++i <= l->ant_count)
		ant[i] = NULL;
	if (!(ant_per_path = (int *)malloc(sizeof(int) * (s->path_count + 1))))
		return (0);
	print_stdin(l);
	write(1, "\n", 1);
	assign_ants_for_pathes(l, s, ant_per_path);
	run_ants(l, s, ant, ant_per_path);
	free(ant);
	free(ant_per_path);
	return (1);
}
