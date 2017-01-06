/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_load_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 11:38:49 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 11:49:37 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

t_me_thing	*create_thing(size_t j, size_t i, int texture)
{
	static t_me_thing	thing;

	thing.pos.x = (double)j;
	thing.pos.y = (double)i;
	thing.texture = texture;
	thing.is_animated = 0;
	return (&thing);
}

void		parse_map_equal(t_me_map *map, char *line)
{
	char	*elem1;
	char	*elem2;

	elem1 = ft_strsub(line, 0, ft_strchr(line, '=') - line);
	elem2 = ft_strsub(line, ft_strchr(line, '=') + 1 -
			line, ft_strlen(line) - (int)(ft_strchr(line, '=') + 1 -
				line));
	if (ft_strcmp(elem1, "name") == 0)
		map->name = elem2;
	else if (ft_strcmp(elem1, "width") == 0)
		map->size.x = ft_atoi(elem2);
	else if (ft_strcmp(elem1, "height") == 0)
		map->size.y = ft_atoi(elem2);
	else if (ft_strcmp(elem1, "tileset") == 0)
		map->tileset = elem2;
	free(elem1);
	free(elem2);
}
