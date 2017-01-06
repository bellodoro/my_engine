/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_create_main_window.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:33:54 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 10:53:28 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <mlx.h>

void	me_create_main_window(t_me_engine *engine)
{
	engine->mlx.win = mlx_new_window(engine->mlx.mlx,
			engine->config.window_size.x, engine->config.window_size.y,
			engine->config.window_name);
	engine->mlx.img.img = mlx_new_image(engine->mlx.mlx,
			engine->config.window_size.x, engine->config.window_size.y);
	engine->mlx.img.pixel = (int*)mlx_get_data_addr(engine->mlx.img.img,
			&engine->mlx.img.bits_per_pixel, &engine->mlx.img.size_line,
			&engine->mlx.img.endian);
}
