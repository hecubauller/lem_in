/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_ant_per_path(t_lem *l, t_solution *s, int *ant_per_path)
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
		if (ant_per_path[i] <= 0)
			break ;
	}
	return (i == s->path_count ? 1 : 0);
}

int				check_solution(t_lem *l, int path_count)
{
	t_solution		*s;
	int				*ant_per_path;

	s = l->solution[path_count - 1];
	if (!(ant_per_path = (int *)malloc(sizeof(int) * (path_count + 1))))
		return (0);
	while (!check_ant_per_path(l, s, ant_per_path) && s->path_count > 1)
	{
		free(s->room[s->path_count - 1]);
		s->path_count--;
	}
	free(ant_per_path);
	return (1);
}

static int		step_forward(t_lem *l, int left_old, int right_old)
{
	int				i;
	int				j;

	i = left_old - 1;
	while (++i < right_old)
	{
		j = -1;
		while (++j < l->queue[i]->tube_count)
			if (l->queue[i]->tube[j]->capacity < MAX_CAPAC &&
				!l->queue[i]->tube[j]->room->prev)
			{
				l->queue[i]->tube[j]->room->prev = l->queue[i]->tube[j]->pair;
				l->queue[l->right] = l->queue[i]->tube[j]->room;
				if (l->queue[l->right] == l->end)
					return (1);
				if (!(++l->right & SIZE_DIFF) &&
					!extend_array((void **)&l->queue, l->right, PTR_SIZE))
					return (-1);
			}
		l->left++;
	}
	return (left_old == l->left || right_old == l->right ? -1 : 0);
}

static int		bfs(t_lem *l)
{
	int				i;
	int				st;
	t_room			*temp_room;

	l->left = 0;
	l->right = 1;
	while (!(st = step_forward(l, l->left, l->right)))
		;
	if (st == 1)
	{
		temp_room = l->end;
		while (temp_room != l->start)
		{
			temp_room->prev->capacity -= 1;
			temp_room->prev->pair->capacity += 1;
			temp_room = temp_room->prev->room;
		}
	}
	i = -1;
	while (++i < l->room_count)
		l->room[i]->prev = NULL;
	return (st == 1 ? 1 : 0);
}

int				find_best_flow(t_lem *l)
{
	int				i;
	int				j;

	if (!(l->queue = (t_room **)malloc(PTR_SIZE * (SIZE_DIFF + 1))))
		return (0);
	l->queue[0] = l->start;
	i = -1;
	while (++i < l->ant_count && bfs(l))
	{
		if (!analyze_current_flow(l, i + 1))
			return (0);
		j = -1;
		while (++j < l->room_count)
			l->room[j]->in_solution = 0;
	}
	return (i ? 1 : 0);
}
