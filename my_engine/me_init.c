/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:26:34 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/13 13:50:51 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

#include <mlx.h>

t_me_engine			*me_init(t_me_config config)
{
	t_me_engine		*engine;

	engine = (t_me_engine*)malloc(sizeof(t_me_engine));
	if (!engine)
		return (0);
	ft_bzero(engine, sizeof(t_me_engine));
	engine->config = config;
	engine->mlx.mlx = mlx_init();
	engine->state_list.running_state = ft_strdup("default");
	engine->state_list.list = 0;
	engine->events.key_pressed = 0;
	engine->events.mouse_move.last_move = (t_me_vector2i){0, 0};
	return (engine);
}
