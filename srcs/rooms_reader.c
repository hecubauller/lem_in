/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_room_name(t_lem *l)
{
	int				i;

	i = -1;
	while (++i < l->room_count)
		if (!ft_strcmp(l->room[i]->name, l->room[l->room_count]->name) ||
			(l->room[i]->x == l->room[l->room_count]->x &&
			l->room[i]->y == l->room[l->room_count]->y))
			return (0);
	return (1);
}

static t_room	*roomalloc(const char *line)
{
	t_room			*room;
	int				i;

	i = 0;
	while (line[i] != ' ')
		i++;
	if (!(room = (t_room *)malloc(ROOM_SIZE)) ||
		!(room->name = ft_strnew(i)))
		return (NULL);
	room->tube = NULL;
	room->tube_count = 0;
	room->prev = NULL;
	room->in_solution = 0;
	room->ant = 0;
	return (room);
}

static int		add_room(t_lem *l, char *line)
{
	int				i;

	if (!(l->room_count & SIZE_DIFF) &&
		!extend_array((void **)&l->room, l->room_count, PTR_SIZE))
		return (0);
	if (!(l->room[l->room_count] = roomalloc(line)))
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	ft_strncpy(l->room[l->room_count]->name, line, i);
	l->flags & F_RSTART ? l->start = l->room[l->room_count] : 0;
	l->flags & F_REND ? l->end = l->room[l->room_count] : 0;
	l->flags & F_RSTART ? l->flags &= ~F_RSTART : 0;
	l->flags & F_REND ? l->flags &= ~F_REND : 0;
	while (line[i] == ' ')
		i++;
	l->room[l->room_count]->x = ft_atoi(line + i);
	while ((line[i] <= '9' && line[i] >= '0') ||
		line[i] == '-' || line[i] == '+')
		i++;
	l->room[l->room_count]->y = ft_atoi(line + i);
	i = check_room_name(l);
	l->room_count++;
	return (i);
}

int				is_add_room(t_lem *l, char *line)
{
	int				i;
	int				temp;

	if (*line <= 32 || *line > 126 || *line == '-' || *line == 'L')
		return (0);
	i = 0;
	while (line[i] > 32 && line[i] <= 126 && line[i] != '-')
		i++;
	if (line[i] != ' ')
		return (0);
	while (line[i] == ' ')
		i++;
	if (!(temp = write_check_num(line + i, &temp)) || line[i + temp] != ' ')
		return (0);
	i += temp;
	while (line[i] == ' ')
		i++;
	if (!(temp = write_check_num(line + i, &temp)) || line[i + temp])
		return (0);
	if ((l->flags & F_START && l->flags & F_RSTART) ||
		(l->flags & F_END && l->flags & F_REND))
		return (0);
	if (l->flags & F_RSTART || l->flags & F_REND)
		l->flags |= l->flags & F_RSTART ? F_START : F_END;
	return (add_room(l, line));
}
