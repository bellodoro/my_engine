/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_raycaster_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:52:54 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/06 14:24:09 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"
#include "stdio.h"
#include <math.h>

static void		reset_pointer(void)
{
}

static void		process_animations(t_raycasting_data *info, t_me_ms delta_time)
{
	t_list		*list;
	t_me_thing	*thing;

	list = info->map->tmap;
	while (list)
	{
		thing = (t_me_thing*)list->content;
		if (thing->is_animated)
			me_process_animation(&thing->animation, delta_time);
		list = list->next;
	}
}

static void		check_pointer_move2(t_me_engine *engine,
		t_raycasting_data *info, double rot_speed, double mouse)
{
	double	old_dir_x;
	double	old_plane_x;

	if (engine->events.mouse_move.last_move.x < 0)
	{
		rot_speed *= mouse * -1;
		old_dir_x = info->player.dir.x;
		info->player.dir.x = info->player.dir.x * cos(-rot_speed) -
			info->player.dir.y * sin(-rot_speed);
		info->player.dir.y = old_dir_x * sin(-rot_speed) + info->player.dir.y
			* cos(-rot_speed);
		old_plane_x = info->player.plane.x;
		info->player.plane.x = info->player.plane.x * cos(-rot_speed) -
			info->player.plane.y * sin(-rot_speed);
		info->player.plane.y = old_plane_x * sin(-rot_speed) +
			info->player.plane.y * cos(-rot_speed);
	}
}

static void		check_pointer_move(t_me_engine *engine, t_raycasting_data *info,
		t_me_ms delta_time)
{
	double	mouse;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.5 * (delta_time / 1000.);
	mouse = engine->events.mouse_move.last_move.x;
	check_pointer_move2(engine, info, rot_speed, mouse);
	if (engine->events.mouse_move.last_move.x > 0)
	{
		rot_speed *= mouse * 1;
		old_dir_x = info->player.dir.x;
		info->player.dir.x = info->player.dir.x * cos(rot_speed) -
			info->player.dir.y * sin(rot_speed);
		info->player.dir.y = old_dir_x * sin(rot_speed) + info->player.dir.y
			* cos(rot_speed);
		old_plane_x = info->player.plane.x;
		info->player.plane.x = info->player.plane.x * cos(rot_speed) -
			info->player.plane.y * sin(rot_speed);
		info->player.plane.y = old_plane_x * sin(rot_speed) +
			info->player.plane.y * cos(rot_speed);
	}
	engine->events.mouse_move.last_move.x = 0;
}

void			me_raycaster_update(t_me_engine *engine, t_me_ms delta_time,
		void *data)
{
	t_raycasting_data	*info;

	if (me_is_key_pressed(KEY_ESCAPE, engine))
		me_exit_game(engine);
	reset_pointer();
	info = (t_raycasting_data*)data;
	process_animations(info, delta_time);
	me_raycaster_process_key_pressed(engine, info, delta_time);
	check_pointer_move(engine, info, delta_time);
}
