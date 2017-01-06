/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_wall_loop1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 18:00:56 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 18:04:16 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <math.h>

void	me_raycaster_wall_loop1(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	x->camera_x = 2 * x->coord.x / (double)engine->config.window_size.x - 1;
	x->ray_pos.x = info->player.pos.x;
	x->ray_pos.y = info->player.pos.y;
	x->ray_dir.x = info->player.dir.x + info->player.plane.x * x->camera_x;
	x->ray_dir.y = info->player.dir.y + info->player.plane.y * x->camera_x;
	x->map.x = (int)x->ray_pos.x;
	x->map.y = (int)x->ray_pos.y;
	x->delta_dist.x = sqrt(1 + (x->ray_dir.y * x->ray_dir.y) /
			(x->ray_dir.x * x->ray_dir.x));
	x->delta_dist.y = sqrt(1 + (x->ray_dir.x * x->ray_dir.x) /
			(x->ray_dir.y * x->ray_dir.y));
	x->hit = 0;
}

void	me_raycaster_wall_loop2(t_me_raycasting_rendering_data *x)
{
	if (x->ray_dir.x < 0)
	{
		x->step.x = -1;
		x->side_dist.x = (x->ray_pos.x - x->map.x) * x->delta_dist.x;
	}
	else
	{
		x->step.x = 1;
		x->side_dist.x = (x->map.x + 1.0 - x->ray_pos.x) * x->delta_dist.x;
	}
	if (x->ray_dir.y < 0)
	{
		x->step.y = -1;
		x->side_dist.y = (x->ray_pos.y - x->map.y) * x->delta_dist.y;
	}
	else
	{
		x->step.y = 1;
		x->side_dist.y = (x->map.y + 1. - x->ray_pos.y) * x->delta_dist.y;
	}
}

void	me_raycaster_wall_loop3(t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	while (x->hit == 0)
	{
		if (x->side_dist.x < x->side_dist.y)
		{
			x->side_dist.x += x->delta_dist.x;
			x->map.x += x->step.x;
			x->side = 0;
		}
		else
		{
			x->side_dist.y += x->delta_dist.y;
			x->map.y += x->step.y;
			x->side = 1;
		}
		if (info->map->wmap[x->map.y][x->map.x] > 0)
			x->hit = 1;
	}
}

void	me_raycaster_wall_loop4(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	if (x->side == 0)
		x->perp_wall_dist = (x->map.x - x->ray_pos.x + (1. - x->step.x) / 2.)
			/ x->ray_dir.x;
	else
		x->perp_wall_dist = (x->map.y - x->ray_pos.y + (1. - x->step.y) / 2.)
			/ x->ray_dir.y;
	x->line_height = (int)((double)engine->config.window_size.y
			/ x->perp_wall_dist);
	x->draw_start = -x->line_height / 2 + engine->config.window_size.y / 2;
	if (x->draw_start < 0)
		x->draw_start = 0;
	x->draw_end = x->line_height / 2 + engine->config.window_size.y / 2;
	if (x->draw_end >= engine->config.window_size.y)
		x->draw_end = engine->config.window_size.y - 1;
	x->tex_num = info->map->wmap[x->map.y][x->map.x] - 1;
	x->tex_info = me_get_texture_information_by_id(x->tex_num, engine);
	if (x->side == 0)
		x->wall_x = x->ray_pos.y + x->perp_wall_dist * x->ray_dir.y;
	else
		x->wall_x = x->ray_pos.x + x->perp_wall_dist * x->ray_dir.x;
	x->wall_x -= floor(x->wall_x);
}

void	me_raycaster_wall_loop5(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	x->tex_x = (int)(x->wall_x * (double)x->tex_info->size.x);
	if (x->side == 0 && x->ray_dir.x > 0)
		x->tex_x = x->tex_info->size.x - x->tex_x - 1;
	if (x->side == 1 && x->ray_dir.y < 0)
		x->tex_x = x->tex_info->size.x - x->tex_x - 1;
	x->y = x->draw_start;
	x->tex = x->tex_info->pixel;
	x->pixel = engine->mlx.img.pixel + x->coord.x
		+ engine->config.window_size.x * x->y;
	while (x->y < x->draw_end)
	{
		x->d = x->y * 2 - engine->config.window_size.y + x->line_height;
		x->tex_y = ((x->d * x->tex_info->size.y) / x->line_height) / 2;
		x->color = x->tex[x->tex_info->size.x * x->tex_y + x->tex_x];
		*x->pixel = x->color;
		x->pixel += engine->config.window_size.x;
		++x->y;
	}
	info->z_buffer[x->coord.x] = x->perp_wall_dist;
}
