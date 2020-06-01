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

static int		is_hash(t_lem *l, char *line)
{
	if (!ft_strcmp(line, COM_START))
	{
		if (l->flags & F_RSTART || l->flags & F_REND)
			return (0);
		l->flags |= F_RSTART;
		return (l->flags & F_ANTS);
	}
	else if (!ft_strcmp(line, COM_END))
	{
		if (l->flags & F_RSTART || l->flags & F_REND)
			return (0);
		l->flags |= F_REND;
		return (l->flags & F_ANTS);
	}
	else if (*line == '#')
		return (1);
	return (0);
}

int				read_check_create_graph(t_lem *l)
{
	int				st;
	char			*line;

	while ((st = get_next_line(0, &line)) > 0)
	{
		if (!(l->stdin_size & SIZE_DIFF) &&
			!extend_array((void **)&l->stdin, l->stdin_size, PTR_SIZE))
			return (0);
		l->stdin[l->stdin_size++] = line;
		if (is_hash(l, line))
			;
		else if (!(l->flags & F_ANTS) && ft_strlen(line) ==
			(size_t)write_check_num(line, &l->ant_count) && l->ant_count > 0)
			l->flags |= F_ANTS;
		else if (l->flags & F_ANTS && !(l->flags & F_ROOMS) &&
			is_add_room(l, line))
			;
		else if (l->flags & F_ANTS && is_add_tube(l, line))
			;
		else
			return (0);
	}
	free(line);
	return (!(l->flags & F_ROOMS) || !(l->flags & F_START) || !(l->flags &
		F_END) || l->flags & F_RSTART || l->flags & F_REND || st < 0 ? 0 : 1);
}
