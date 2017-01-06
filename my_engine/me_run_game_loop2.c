/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_run_game_loop2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 12:08:53 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 14:50:48 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"
#include <time.h>
#include <sys/time.h>

#include <mlx.h>

void		print_fps_counter(double time_in_mill)
{
	static double fps = 0;
	static double fps_time = 0;

	++fps;
	fps_time += time_in_mill;
	if (fps == 120.)
	{
		ft_printf("%d FPS\n", (int)(1. / (fps_time / fps / 1000.)));
		fps = 0;
		fps_time = 0;
	}
}

void		print_image(t_me_engine *engine)
{
	int				ok;
	static void		*img = 0;
	static char		*data = 0;

	if (!img)
		img = mlx_new_image(engine->mlx.mlx,
				engine->config.window_size.x, engine->config.window_size.y);
	if (!data)
		data = mlx_get_data_addr(img, &ok, &ok, &ok);
	ft_memcpy(data, engine->mlx.img.pixel, sizeof(int)
			* engine->config.window_size.x * engine->config.window_size.y);
	mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
			img, 0, 0);
}

double		compute_time(t_me_engine *engine, double *start, double *end)
{
	struct timeval	tv;
	double			time_in_mill;
	double			time_in_mill2;

	gettimeofday(&tv, NULL);
	time_in_mill = (double)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	time_in_mill2 = time_in_mill - *start;
	if (*start != 0)
	{
		*end = time_in_mill;
		if (*end - *start < engine->config.framerate * 1000.)
			return (0);
	}
	if (*start == 0)
	{
		*start = time_in_mill;
		return (0);
	}
	*start = time_in_mill;
	return (time_in_mill2);
}
