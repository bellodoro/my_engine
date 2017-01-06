/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splashscreen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 12:15:11 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 17:53:52 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	splashscreen_update(t_me_engine *engine, t_me_ms delta_time, void *data)
{
	static t_me_ms	total_time = 0;

	(void)data;
	total_time += delta_time;
	if (total_time >= 5000.)
	{
		free(engine->state_list.running_state);
		engine->state_list.running_state = ft_strdup("default");
	}
}

void	splashscreen_render(t_me_engine *engine, void *data, int begin, int end)
{
	int				y;
	int				x;
	int				*color;
	t_me_texture	*info;

	(void)end;
	(void)data;
	if (begin != 0)
		return ;
	color = me_get_texture_data_by_id(300, engine);
	info = me_get_texture_information_by_id(300, engine);
	y = 0;
	while (y < info->size.y)
	{
		x = 0;
		while (x < info->size.x)
		{
			engine->mlx.img.pixel[y * engine->config.window_size.x + x] =
				color[y * info->size.x + x];
			++x;
		}
		++y;
	}
}

void	init_splashscreen_state(t_me_engine *engine)
{
	t_me_state	*state;

	state = (t_me_state*)malloc(sizeof(t_me_state));
	state->name = ft_strdup("splashscreen");
	state->update = splashscreen_update;
	state->render = splashscreen_render;
	state->data = 0;
	me_add_state(engine, state);
	free(engine->state_list.running_state);
	engine->state_list.running_state = ft_strdup("splashscreen");
}
