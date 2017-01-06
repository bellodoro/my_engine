/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_mouse_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 11:51:06 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 11:51:08 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		me_mouse_move(int x, int y, void *param)
{
	t_me_engine				*engine;
	static t_me_vector2i	last_position = {0, 0};

	engine = (t_me_engine*)param;
	if (last_position.x == 0)
		last_position.x = x;
	if (last_position.y == 0)
		last_position.y = y;
	engine->events.mouse_move.last_move.x = last_position.x - x;
	engine->events.mouse_move.last_move.y = last_position.y - y;
	last_position.x = x;
	last_position.y = y;
	return (0);
}
