/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_room_name(t_lem *l, char *name)
{
	int				i;

	i = -1;
	while (++i < l->room_count)
		if (!ft_strcmp(l->room[i]->name, name))
			return (i);
	return (-1);
}

static int		check_tube_exist(t_lem *l, int a, int b)
{
	int				i;

	i = -1;
	while (++i < l->room[b]->tube_count)
		if (!ft_strcmp(l->room[a]->name, l->room[b]->tube[i]->room->name))
			return (1);
	return (0);
}

static int		add_tube(t_lem *l, int a, int b)
{
	if ((!(l->room[a]->tube_count & SIZE_DIFF) && !extend_array(
		(void **)&l->room[a]->tube, l->room[a]->tube_count, PTR_SIZE)) ||
		(!(l->room[b]->tube_count & SIZE_DIFF) && !extend_array(
		(void **)&l->room[b]->tube, l->room[b]->tube_count, PTR_SIZE)))
		return (0);
	if (!(l->room[a]->tube[l->room[a]->tube_count] =
		(t_tube *)malloc(TUBE_SIZE)) ||
		!(l->room[b]->tube[l->room[b]->tube_count] =
		(t_tube *)malloc(TUBE_SIZE)))
		return (0);
	l->room[a]->tube[l->room[a]->tube_count]->room = l->room[b];
	l->room[a]->tube[l->room[a]->tube_count]->capacity = 0;
	l->room[a]->tube[l->room[a]->tube_count]->pair =
		l->room[b]->tube[l->room[b]->tube_count];
	l->room[b]->tube[l->room[b]->tube_count]->room = l->room[a];
	l->room[b]->tube[l->room[b]->tube_count]->capacity = 0;
	l->room[b]->tube[l->room[b]->tube_count]->pair =
			l->room[a]->tube[l->room[a]->tube_count];
	l->room[a]->tube_count++;
	l->room[b]->tube_count++;
	return (1);
}

int				is_add_tube(t_lem *l, char *line)
{
	int				index[2];
	int				i;

	if (l->flags & F_RSTART || l->flags & F_REND)
		return (0);
	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] != '-')
		return (0);
	line[i] = '\0';
	if ((index[0] = check_room_name(l, line)) == -1 ||
		(index[1] = check_room_name(l, line + i + 1)) == -1 ||
		check_tube_exist(l, index[0], index[1]))
		return (0);
	line[i] = '-';
	l->flags |= F_ROOMS;
	return (add_tube(l, index[0], index[1]));
}
