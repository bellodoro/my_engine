/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_load_map01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:59:15 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/05 12:07:21 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

void	norme1(int j, t_me_map *map, char **split, int *i)
{
	if (j != map->size.x)
		me_die("invalid map");
	if (split[j])
		free(split[j]);
	++(*i);
	free(split);
}

void	norme2(int j, t_me_map *map, int *i, char *line)
{
	if (j != map->size.x)
		me_die("invalid_map");
	++(*i);
	free(line);
}
