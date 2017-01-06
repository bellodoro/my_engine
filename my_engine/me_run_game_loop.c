/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_run_game_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:36:20 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 11:56:57 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <mlx.h>
#include <unistd.h>
#include <pthread.h>

#include "stdio.h"

static void		*start_render_thread(void *data)
{
	t_me_thread_render	*thread;
	t_me_engine			*engine;
	t_me_state			*state;

	thread = (t_me_thread_render*)data;
	engine = thread->engine;
	state = me_get_state(engine, engine->state_list.running_state);
	state->render(engine, state->data, thread->id
			* (engine->config.window_size.x / THREAD_NUMBER), (thread->id + 1)
			* (engine->config.window_size.x / THREAD_NUMBER));
	free(thread);
	return (0);
}

static void		start_render_threads(t_me_engine *engine)
{
	pthread_t			threads[THREAD_NUMBER];
	int					i;
	t_me_thread_render	*t;

	i = 0;
	while (i < THREAD_NUMBER)
	{
		t = malloc(sizeof(t_me_thread_render));
		t->engine = engine;
		t->id = i;
		pthread_create(&threads[i], NULL, start_render_thread, (void*)t);
		++i;
	}
	i = 0;
	while (i < THREAD_NUMBER)
		pthread_join(threads[i++], NULL);
}

static int				me_game_loop(void *param)
{
	t_me_engine		*engine;
	t_me_state		*state;
	static double	start = 0;
	static double	end = 0;
	double			time_in_mill;

	engine = (t_me_engine*)param;
	time_in_mill = compute_time(engine, &start, &end);
	if (!time_in_mill)
		return (0);
	state = me_get_state(engine, engine->state_list.running_state);
	if (state->update)
		state->update(engine, time_in_mill, state->data);
	if (state->render)
		start_render_threads(engine);
	print_fps_counter(time_in_mill);
	print_image(engine);
	return (0);
}

void			me_run_game_loop(t_me_engine *engine)
{
	mlx_loop_hook(engine->mlx.mlx, me_game_loop, (void*)engine);
	mlx_hook(engine->mlx.win, 2, 1L << 0, me_key_press, engine);
	mlx_hook(engine->mlx.win, 3, 1L << 1, me_key_release, engine);
	mlx_hook(engine->mlx.win, 6, 64, me_mouse_move, engine);
	mlx_hook(engine->mlx.win, 17, 1L << 17, me_exit_game, engine);
	mlx_loop(engine->mlx.mlx);
}
