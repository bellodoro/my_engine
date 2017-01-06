/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_wall_lopp2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 17:53:32 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/05 11:50:43 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <math.h>

void	me_raycaster_wall_loop6(t_me_raycasting_rendering_data *x)
{
	if (x->side == 0 && x->ray_dir.x > 0)
	{
		x->floor_wall.x = x->map.x;
		x->floor_wall.y = x->map.y + x->wall_x;
	}
	else if (x->side == 0 && x->ray_dir.x < 0)
	{
		x->floor_wall.x = x->map.x + 1.0;
		x->floor_wall.y = x->map.y + x->wall_x;
	}
	else if (x->side == 1 && x->ray_dir.y > 0)
	{
		x->floor_wall.x = x->map.x + x->wall_x;
		x->floor_wall.y = x->map.y;
	}
	else
	{
		x->floor_wall.x = x->map.x + x->wall_x;
		x->floor_wall.y = x->map.y + 1.0;
	}
}

void	me_raycaster_wall_loop7(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	x->dist_wall = x->perp_wall_dist;
	x->dist_player = 0.;
	if (x->draw_end < 0)
		x->draw_end = engine->config.window_size.y;
	x->y = x->draw_end + 1;
	x->ftex_info = me_get_texture_information_by_id(
			info->map->fmap[x->map.y][x->map.x] - 1, engine);
	x->ftex = x->ftex_info->pixel;
	x->ctex_info = me_get_texture_information_by_id(
			info->map->cmap[x->map.y][x->map.x] - 1, engine);
	x->ctex = x->ctex_info->pixel;
	--x->y;
}

void	me_raycaster_wall_loop8_1(t_me_engine *engine,
		t_me_raycasting_rendering_data *x)
{
	x->cloor_tex.y = (int)(x->current_floor.y * x->ctex_info->size.y)
		% x->ctex_info->size.y;
	engine->mlx.img.pixel[(engine->config.window_size.x * x->y) + x->coord.x] =
		(x->ftex_info->pixel[(int)(x->ftex_info->size.x * x->floor_tex.y
							+ x->floor_tex.x)] >> 1) & 8355711;
	engine->mlx.img.pixel[engine->config.window_size.x
		* (engine->config.window_size.y - x->y - 1) + x->coord.x] =
		(x->ctex_info->pixel[(int)(x->ctex_info->size.x * x->cloor_tex.y
					+ x->cloor_tex.x)] >> 1) & 8355711;
	++x->y;
}

void	me_raycaster_wall_loop8(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	x->current_dist = engine->config.window_size.y /
		(2.0 * x->y - engine->config.window_size.y);
	x->weight = (x->current_dist - x->dist_player)
		/ (x->dist_wall - x->dist_player);
	x->current_floor.x = x->weight * x->floor_wall.x + (1.0 - x->weight)
		* info->player.pos.x;
	x->current_floor.y = x->weight * x->floor_wall.y + (1.0 - x->weight)
		* info->player.pos.y;
	if (x->current_floor.y > info->map->size.y)
		x->current_floor.y = info->map->size.y - 1;
	if (x->current_floor.x > info->map->size.x)
		x->current_floor.x = info->map->size.x - 1;
	x->current_floor.x = (x->current_floor.x < 0) ? 0 : x->current_floor.x;
	x->current_floor.y = (x->current_floor.y < 0) ? 0 : x->current_floor.y;
	x->ftex_info = me_get_texture_information_by_id(info->map->fmap
			[(int)x->current_floor.y][(int)x->current_floor.x] - 1, engine);
	x->ctex_info = me_get_texture_information_by_id(info->map->cmap
			[(int)x->current_floor.y][(int)x->current_floor.x] - 1, engine);
	x->floor_tex.x = (int)(x->current_floor.x * x->ftex_info->size.x)
		% x->ftex_info->size.x;
	x->floor_tex.y = (int)(x->current_floor.y * x->ftex_info->size.y)
		% x->ftex_info->size.y;
	x->cloor_tex.x = (int)(x->current_floor.x * x->ctex_info->size.x)
		% x->ctex_info->size.x;
	me_raycaster_wall_loop8_1(engine, x);
}

void	me_raycaster_wall_loop(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	me_raycaster_wall_loop1(engine, info, x);
	me_raycaster_wall_loop2(x);
	me_raycaster_wall_loop3(info, x);
	me_raycaster_wall_loop4(engine, info, x);
	me_raycaster_wall_loop5(engine, info, x);
	me_raycaster_wall_loop6(x);
	me_raycaster_wall_loop7(engine, info, x);
	while (x->y < engine->config.window_size.y)
		me_raycaster_wall_loop8(engine, info, x);
}
