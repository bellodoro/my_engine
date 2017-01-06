/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_key_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:20:32 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 14:40:12 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		me_key_release(int keycode, void *param)
{
	t_me_engine				*engine;
	t_list					*list;

	engine = (t_me_engine*)param;
	list = engine->events.key_pressed;
	while (list)
	{
		if (((t_me_events_key_press*)(list->content))->keycode == keycode)
		{
			((t_me_events_key_press*)(list->content))->is_pressed = 0;
			return (1);
		}
		list = list->next;
	}
	return (0);
}
