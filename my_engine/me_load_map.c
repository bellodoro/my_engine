/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_load_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:33:22 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/05 12:09:05 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <fcntl.h>
#include <unistd.h>

static void			parse_things(int fd, t_me_map *map)
{
	char	*line;
	char	**split;
	int		thing;
	int		i;
	int		j;

	map->tmap = 0;
	i = 0;
	while (i < map->size.y && ft_get_next_line(fd, &line) && ft_isdigit(*line))
	{
		split = ft_strsplit(line, ' ');
		j = -1;
		while (++j < map->size.x && split[j])
		{
			thing = ft_atoi(split[j]);
			if (thing)
				ft_lstadd(&map->tmap, ft_lstnew(create_thing(j, i, thing),
							sizeof(t_me_thing)));
			free(split[j]);
		}
		norme2(j, map, &i, line);
		free(split);
	}
	if (i != map->size.y)
		me_die("invalid_map");
}

static void			parse_coordinates2(int fd, t_me_map *map, char *line,
		int ***map_elem)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	while (i < map->size.y && ft_get_next_line(fd, &line) && ft_isdigit(*line))
	{
		split = ft_strsplit(line, ' ');
		free(line);
		line = 0;
		(*map_elem)[i] = (int*)malloc(sizeof(int) * map->size.x);
		j = 0;
		while (j < map->size.x && split[j])
		{
			(*map_elem)[i][j] = ft_atoi(split[j]);
			free(split[j]);
			++j;
		}
		norme1(j, map, split, &i);
	}
	if (i != map->size.y)
		me_die("invalid map");
	if (line)
		free(line);
}

static void			parse_coordinates(int fd, t_me_map *map, char *line,
		char *begin)
{
	char	*end;
	char	*elem;
	int		***map_elem;

	begin = ft_strchr(line, '(') + 1;
	end = ft_strchr(line, ')');
	elem = ft_strsub(line, begin - line, end - begin);
	if (ft_strcmp("wmap", elem) == 0)
		map_elem = &map->wmap;
	else if (ft_strcmp("fmap", elem) == 0)
		map_elem = &map->fmap;
	else if (ft_strcmp("cmap", elem) == 0)
		map_elem = &map->cmap;
	else if (ft_strcmp("bmap", elem) == 0)
		map_elem = &map->bmap;
	else if (ft_strcmp("tmap", elem) == 0)
	{
		free(elem);
		return (parse_things(fd, map));
	}
	else
		return (free(elem));
	*map_elem = (int**)malloc(sizeof(int*) * map->size.y);
	parse_coordinates2(fd, map, line, map_elem);
	free(elem);
}

static void			parse_map(int fd, t_me_map *map)
{
	char	*line;

	while (ft_get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 256)
			me_die("invalid map");
		if (*line == '#')
		{
			free(line);
			continue;
		}
		if (ft_strchr(line, '=') != 0)
			parse_map_equal(map, line);
		else if (ft_strchr(line, '('))
			parse_coordinates(fd, map, line, 0);
		free(line);
		line = 0;
	}
	if (line)
		free(line);
}

t_me_map			*me_load_map(char *file)
{
	int			fd;
	t_me_map	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		me_die("map not found");
	map = (t_me_map*)malloc(sizeof(t_me_map));
	if (!map)
		me_die("not enough memory");
	ft_bzero(map, sizeof(t_me_map));
	parse_map(fd, map);
	close(fd);
	if (!map->name || !map->wmap || !map->bmap || !map->fmap || !map->cmap
			|| !map->tmap)
		me_die("incomplete map");
	return (map);
}
