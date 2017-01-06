/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:22:30 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 17:58:46 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	load_textures2(t_me_engine *engine)
{
	me_load_texture("enter2.xpm", 22, "textures/enter2.xpm", engine);
	me_load_texture("welcome.xpm", 23, "textures/welcome.xpm", engine);
	me_load_texture("triss.xpm", 24, "textures/triss.xpm", engine);
	me_load_texture("nathan.xpm", 30, "textures/nathan.xpm", engine);
	me_load_texture("gautier.xpm", 29, "textures/gautier.xpm", engine);
	me_load_texture("gaetan.xpm", 31, "textures/gaetan.xpm", engine);
	me_load_texture("ennemy1.xpm", 39, "textures/ennemy1.xpm", engine);
	me_load_texture("ennemy2.xpm", 40, "textures/ennemy2.xpm", engine);
	me_load_texture("geralt.xpm", 41, "textures/geralt.xpm", engine);
	me_load_texture("crosshair.xpm", 100, "textures/crosshair.xpm", engine);
	me_load_texture("grass.xpm", 199, "textures/grass.xpm", engine);
	me_load_texture("brick_unicorn.xpm", 200, "textures/brick_unicorn.xpm",
			engine);
	me_load_texture("wood2.xpm", 201, "textures/wood2.xpm", engine);
	me_load_texture("wood3.xpm", 202, "textures/wood3.xpm", engine);
	me_load_texture("metal.xpm", 203, "textures/metal.xpm", engine);
	me_load_texture("sand.xpm", 204, "textures/sand.xpm", engine);
	me_load_texture("illuminati.xpm", 205, "textures/illuminati.xpm", engine);
	me_load_texture("rock4.xpm", 206, "textures/rock4.xpm", engine);
	me_load_texture("splash.png", 300, "textures/splash.xpm", engine);
}

void	load_textures(t_me_engine *engine)
{
	me_load_texture("eagle.xpm", 0, "textures/eagle.xpm", engine);
	me_load_texture("redbrick.xpm", 1, "textures/redbrick.xpm", engine);
	me_load_texture("purplestone.xpm", 2, "textures/purplestone.xpm", engine);
	me_load_texture("greystone.xpm", 3, "textures/greystone.xpm", engine);
	me_load_texture("bluestone.xpm", 4, "textures/bluestone.xpm", engine);
	me_load_texture("mossy.xpm", 5, "textures/mossy.xpm", engine);
	me_load_texture("wood.xpm", 6, "textures/wood.xpm", engine);
	me_load_texture("colorstone.xpm", 7, "textures/brick.xpm", engine);
	me_load_texture("barrel.xpm", 8, "textures/barrel.xpm", engine);
	me_load_texture("pillar.xpm", 9, "textures/pillar.xpm", engine);
	me_load_texture("greenlight.xpm", 10, "textures/greenlight.xpm", engine);
	me_load_texture("floor1.xpm", 11, "textures/floor1.xpm", engine);
	me_load_texture("ceiling1.xpm", 12, "textures/ceiling1.xpm", engine);
	me_load_texture("chest1.xpm", 13, "textures/chest1.xpm", engine);
	me_load_texture("charlie1.xpm", 14, "textures/charlie1.xpm", engine);
	me_load_texture("charlie2.xpm", 15, "textures/charlie2.xpm", engine);
	me_load_texture("eridou.xpm", 19, "textures/eridu.xpm", engine);
	me_load_texture("canyou.xpm", 20, "textures/canyou.xpm", engine);
	me_load_texture("enter1.xpm", 21, "textures/enter1.xpm", engine);
	load_textures2(engine);
}

void	animate_guards(t_me_state *state)
{
	t_me_map	*map;
	t_list		*list;
	t_me_thing	*thing;

	map = ((t_raycasting_data*)state->data)->map;
	list = map->tmap;
	while (list)
	{
		thing = (t_me_thing*)list->content;
		if (thing->texture == 40 || thing->texture == 41)
		{
			thing->is_animated = 1;
			thing->animation.number_of_frame = 2;
			thing->animation.current_frame = thing->texture - 40;
			thing->animation.first_texture_id = 39;
			thing->animation.millis_between_frames = 750.;
			thing->animation.time_of_last_frame = 0.;
		}
		list = list->next;
	}
}

void	init_default_state(t_me_engine *engine)
{
	t_me_state	*default_state;

	default_state = (t_me_state*)malloc(sizeof(t_me_state));
	default_state->name = ft_strdup("default");
	default_state->update = me_raycaster_update;
	default_state->render = me_raycaster_render;
	default_state->data = (t_raycasting_data*)malloc(sizeof(t_raycasting_data));
	ft_bzero(default_state->data, sizeof(t_raycasting_data));
	((t_raycasting_data*)default_state->data)->map = me_load_map("map.me");
	animate_guards(default_state);
	((t_raycasting_data*)default_state->data)->player.pos.x = 3;
	((t_raycasting_data*)default_state->data)->player.pos.y = 2;
	((t_raycasting_data*)default_state->data)->player.dir.x = -1;
	((t_raycasting_data*)default_state->data)->player.dir.y = 0;
	((t_raycasting_data*)default_state->data)->player.plane.x = 0;
	((t_raycasting_data*)default_state->data)->player.plane.y = 0.95;
	((t_raycasting_data*)default_state->data)->z_buffer =
		(double*)malloc(sizeof(double) * engine->config.window_size.x);
	ft_bzero(((t_raycasting_data*)default_state->data)->z_buffer,
			sizeof(double) * engine->config.window_size.x);
	me_add_state(engine, default_state);
}

int		main(void)
{
	t_me_config		config;
	t_me_engine		*engine;

	config.window_size.x = 1280;
	config.window_size.y = 720;
	config.window_name = "Wolf3d by Martin";
	config.framerate = FPS_60;
	engine = me_init(config);
	init_splashscreen_state(engine);
	init_default_state(engine);
	load_textures(engine);
	me_create_main_window(engine);
	me_run_game_loop(engine);
}
