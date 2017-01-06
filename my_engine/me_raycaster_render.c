/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 15:41:47 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 14:05:05 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <math.h>

void	me_raycaster_print_crosshair(t_me_engine *engine)
{
	t_me_texture	*crosshair;
	int				x;
	int				y;
	int				x2;
	int				y2;

	crosshair = me_get_texture_information_by_id(100, engine);
	y = engine->config.window_size.y / 2 - crosshair->size.y / 2;
	y2 = 0;
	while (y < engine->config.window_size.y / 2 + crosshair->size.y / 2)
	{
		x = engine->config.window_size.x / 2 - crosshair->size.x / 2;
		x2 = 0;
		while (x < engine->config.window_size.x / 2 + crosshair->size.x / 2)
		{
			if ((crosshair->pixel
						[y2 * crosshair->size.x + x2] & 0x00ffffff) != 0)
				engine->mlx.img.pixel[y * engine->config.window_size.x + x] =
					crosshair->pixel[y2 * crosshair->size.x + x2];
			++x;
			++x2;
		}
		++y;
		++y2;
	}
}

void	me_raycaster_render(t_me_engine *engine, void *data, int begin, int end)
{
	t_raycasting_data				*info;
	t_me_raycasting_rendering_data	x;
	int								i;

	info = (t_raycasting_data*)data;
	x.coord.x = begin;
	while (x.coord.x < end)
	{
		me_raycaster_wall_loop(engine, info, &x);
		++x.coord.x;
	}
	me_raycaster_thing1(info, &x);
	i = 0;
	while (i < x.num_sprites)
	{
		me_raycaster_thing_loop1(engine, info, &x, i);
		me_raycaster_thing_loop2(engine, &x);
		me_raycaster_thing_loop3(engine, info, &x);
		++i;
	}
	free(x.sprite_order);
	free(x.sprite_distance);
	me_raycaster_print_crosshair(engine);
}
