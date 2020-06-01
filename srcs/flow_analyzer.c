/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		solalloc(t_lem *l, int path_count)
{
	int				i;

	if (!((path_count - 1) & SIZE_DIFF) &&
		!extend_array((void **)&l->solution, path_count - 1, PTR_SIZE))
		return (0);
	l->solution_count++;
	if (!(l->solution[path_count - 1] =
		(t_solution *)malloc(sizeof(t_solution))))
		return (0);
	if (!(l->solution[path_count - 1]->room =
		(t_room ***)malloc(PTR_SIZE * path_count)))
		return (0);
	if (!(l->solution[path_count - 1]->path_length =
		(int *)malloc(sizeof(int) * path_count)))
		return (0);
	i = -1;
	while (++i < path_count)
		l->solution[path_count - 1]->path_length[i] = 0;
	l->solution[path_count - 1]->path_sum_length = 0;
	l->solution[path_count - 1]->turn_count = 0;
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
			if (l->queue[i]->tube[j]->capacity == MAX_CAPAC &&
				!l->queue[i]->tube[j]->room->prev &&
				!l->queue[i]->tube[j]->room->in_solution)
			{
				l->queue[i]->tube[j]->room->prev = l->queue[i]->tube[j]->pair;
				l->queue[l->right] = l->queue[i]->tube[j]->room;
				if (l->queue[l->right] == l->end)
					return (1);
				if (!(++l->right & SIZE_DIFF) &&
					!extend_array((void **)&l->queue, l->right, PTR_SIZE))
					return (-2);
			}
		l->left++;
	}
	return (left_old == l->left || right_old == l->right ? -1 : 0);
}

static int		write_path(t_lem *l, int path, int path_count)
{
	int				i;
	t_room			*temp_room;

	temp_room = l->end;
	while (temp_room != l->start)
	{
		l->solution[path_count - 1]->path_length[path]++;
		temp_room = temp_room->prev->room;
	}
	if (!(l->solution[path_count - 1]->room[path] = (t_room **)malloc(
		PTR_SIZE * (l->solution[path_count - 1]->path_length[path] + 1))))
		return (0);
	temp_room = l->end;
	i = l->solution[path_count - 1]->path_length[path] + 1;
	while (--i > 0)
	{
		l->solution[path_count - 1]->room[path][i] = temp_room;
		temp_room->prev->room->in_solution = 1;
		temp_room = temp_room->prev->room;
	}
	l->solution[path_count - 1]->room[path][0] = temp_room;
	l->solution[path_count - 1]->path_sum_length +=
		l->solution[path_count - 1]->path_length[path];
	return (1);
}

static int		bfs(t_lem *l, int path, int path_count)
{
	int				i;
	int				st;

	l->left = 0;
	l->right = 1;
	while (!(st = step_forward(l, l->left, l->right)))
		;
	if (st == 1 && !write_path(l, path, path_count))
		return (-2);
	i = -1;
	while (++i < l->room_count)
		l->room[i]->prev = NULL;
	return (st);
}

int				analyze_current_flow(t_lem *l, int path_count)
{
	int				i;
	int				st;

	if (!solalloc(l, path_count))
		return (0);
	i = -1;
	while (++i < path_count)
		if ((st = bfs(l, i, path_count)) != 1)
			break ;
	l->solution[path_count - 1]->path_count = i;
	if (!i || st == -2)
		return (st == -2 ? 0 : -1);
	if (!check_solution(l, path_count))
		return (0);
	l->solution[path_count - 1]->turn_count =
		(l->ant_count + l->solution[path_count - 1]->path_sum_length);
	l->solution[path_count - 1]->turn_count =
		l->solution[path_count - 1]->turn_count /
		l->solution[path_count - 1]->path_count +
		(!(l->solution[path_count - 1]->turn_count %
		l->solution[path_count - 1]->path_count) ? -1 : 0);
	if (l->solution[path_count - 1]->turn_count <
		l->solution[l->best_solution]->turn_count)
		l->best_solution = path_count - 1;
	return (1);
}
