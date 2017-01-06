/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 13:04:53 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 13:10:40 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <math.h>

static void		me_raycaster_move_forward(t_raycasting_data *info,
		double move_speed)
{
	if (info->map->bmap[(int)info->player.pos.y]
			[(int)(info->player.pos.x + info->player.dir.x * move_speed)] == 0)
		info->player.pos.x += info->player.dir.x * move_speed;
	if (info->map->bmap[(int)(info->player.pos.y + info->player.dir.y
				* move_speed)][(int)info->player.pos.x] == 0)
		info->player.pos.y += info->player.dir.y * move_speed;
}

static void		me_raycaster_move_backward(t_raycasting_data *info,
		double move_speed)
{
	if (info->map->bmap[(int)info->player.pos.y]
			[(int)(info->player.pos.x - info->player.dir.x * move_speed)] == 0)
		info->player.pos.x -= info->player.dir.x * move_speed;
	if (info->map->bmap[(int)(info->player.pos.y - info->player.dir.y
				* move_speed)][(int)info->player.pos.x] == 0)
		info->player.pos.y -= info->player.dir.y * move_speed;
}

static void		me_raycaster_move_left(t_raycasting_data *info,
		double move_speed)
{
	t_me_vector2d dir;

	dir.x = info->player.dir.x * cos(58) - info->player.dir.y * sin(58);
	dir.y = info->player.dir.x * sin(58) + info->player.dir.y * cos(58);
	if (info->map->bmap[(int)(info->player.pos.y + dir.y * move_speed)]
			[(int)(info->player.pos.x + dir.x * move_speed)] == 0)
		info->player.pos.x += dir.x * move_speed;
	if (info->map->bmap[(int)(info->player.pos.y + dir.y * move_speed)]
			[(int)(info->player.pos.x + dir.x * move_speed)] == 0)
		info->player.pos.y += dir.y * move_speed;
}

static void		me_raycaster_move_right(t_raycasting_data *info,
		double move_speed)
{
	t_me_vector2d dir;

	dir.x = info->player.dir.x * cos(58) - info->player.dir.y * sin(58);
	dir.y = info->player.dir.x * sin(58) + info->player.dir.y * cos(58);
	if (info->map->bmap[(int)(info->player.pos.y - dir.y * move_speed)]
			[(int)(info->player.pos.x - dir.x * move_speed)] == 0)
		info->player.pos.x -= dir.x * move_speed;
	if (info->map->bmap[(int)(info->player.pos.y - dir.y * move_speed)]
			[(int)(info->player.pos.x - dir.x * move_speed)] == 0)
		info->player.pos.y -= dir.y * move_speed;
}

void			me_raycaster_process_key_pressed(t_me_engine *engine,
		t_raycasting_data *info, t_me_ms delta_time)
{
	double	move_speed;

	move_speed = 5 * (delta_time / 1000.);
	if (me_is_key_pressed(KEY_W, engine) || me_is_key_pressed(KEY_UP, engine))
		me_raycaster_move_forward(info, move_speed);
	if (me_is_key_pressed(KEY_S, engine) || me_is_key_pressed(KEY_DOWN, engine))
		me_raycaster_move_backward(info, move_speed);
	if (me_is_key_pressed(KEY_A, engine) || me_is_key_pressed(KEY_LEFT, engine))
		me_raycaster_move_left(info, move_speed);
	if (me_is_key_pressed(KEY_D, engine)
			|| me_is_key_pressed(KEY_RIGHT, engine))
		me_raycaster_move_right(info, move_speed);
}
