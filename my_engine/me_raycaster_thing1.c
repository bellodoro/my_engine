/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_thing1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 17:56:44 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 14:05:20 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <math.h>

void	me_raycaster_thing1(t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	int		i;

	x->num_sprites = ft_lstcount(info->map->tmap);
	x->sprite_order = malloc(sizeof(int) * x->num_sprites);
	x->sprite_distance = malloc(sizeof(double) * x->num_sprites);
	x->things = info->map->tmap;
	i = 0;
	while (i < x->num_sprites)
	{
		x->thing = (t_me_thing*)x->things->content;
		x->sprite_order[i] = i;
		x->sprite_distance[i] = ((info->player.pos.x - x->thing->pos.x)
				* (info->player.pos.x - x->thing->pos.x)
				+ (info->player.pos.y - x->thing->pos.y)
				* (info->player.pos.y - x->thing->pos.y));
		x->things = x->things->next;
		++i;
	}
	me_thing_combsort(x->sprite_order, x->sprite_distance, x->num_sprites);
}

void	me_raycaster_thing_loop1(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x, int i)
{
	x->thing = (t_me_thing*)ft_lstat(info->map->tmap,
			x->sprite_order[i])->content;
	x->sprite_x = x->thing->pos.x - info->player.pos.x;
	x->sprite_y = x->thing->pos.y - info->player.pos.y;
	x->inv_det = 1.0 / (info->player.plane.x * info->player.dir.y
			- info->player.dir.x * info->player.plane.y);
	x->transform_x = x->inv_det * (info->player.dir.y * x->sprite_x
			- info->player.dir.x * x->sprite_y);
	x->transform_y = x->inv_det * (-info->player.plane.y * x->sprite_x
			+ info->player.plane.x * x->sprite_y);
	x->sprite_screen_x = (int)((engine->config.window_size.x / 2)
			* (1 + x->transform_x / x->transform_y));
	x->sprite_height = abs((int)(engine->config.window_size.y
				/ x->transform_y));
	x->draw_start_y = -x->sprite_height / 2 + engine->config.window_size.y / 2;
	if (x->draw_start_y < 0)
		x->draw_start_y = 0;
	x->draw_end_y = x->sprite_height / 2 + engine->config.window_size.y / 2;
	if (x->draw_end_y >= engine->config.window_size.y)
		x->draw_end_y = engine->config.window_size.y - 1;
}

void	me_raycaster_thing_loop2(t_me_engine *engine,
		t_me_raycasting_rendering_data *x)
{
	x->sprite_width = abs((int)(engine->config.window_size.y / x->transform_y));
	x->draw_start_x = -x->sprite_width / 2 + x->sprite_screen_x;
	if (x->draw_start_x < 0)
		x->draw_start_x = 0;
	x->draw_end_x = x->sprite_width / 2 + x->sprite_screen_x;
	if (x->draw_end_x >= engine->config.window_size.x)
		x->draw_end_x = engine->config.window_size.x - 1;
	x->texture_id = x->thing->texture - 1;
	if (x->thing->is_animated)
		x->texture_id = me_get_texture_for_animation(&x->thing->animation);
	x->tex2 = me_get_texture_information_by_id(x->texture_id, engine);
}

void	me_raycaster_thing_loop3(t_me_engine *engine, t_raycasting_data *info,
		t_me_raycasting_rendering_data *x)
{
	int	stripe;
	int	y;

	stripe = x->draw_start_x;
	while (stripe < x->draw_end_x)
	{
		x->tex_x = (int)((stripe - (-x->sprite_width / 2 + x->sprite_screen_x))
				* x->tex2->size.x / x->sprite_width);
		if (x->transform_y > 0 && stripe < engine->config.window_size.x
				&& x->transform_y < info->z_buffer[stripe] && stripe > 0)
		{
			y = x->draw_start_y - 1;
			while (++y < x->draw_end_y)
			{
				x->d = y * 2 - engine->config.window_size.y + x->sprite_height;
				x->tex_y = ((x->d * x->tex2->size.y) / x->sprite_height) / 2;
				x->color = x->tex2->pixel[x->tex2->size.x * x->tex_y
					+ x->tex_x];
				if ((x->color & 0x00ffffff) != 0)
					engine->mlx.img.pixel[engine->config.window_size.x * y
						+ stripe] = x->color;
			}
		}
		++stripe;
	}
}
