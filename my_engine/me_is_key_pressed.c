/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_is_key_pressed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:21:01 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 11:00:33 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		me_is_key_pressed(int keycode, t_me_engine *engine)
{
	t_list					*list;

	list = engine->events.key_pressed;
	while (list)
	{
		if (((t_me_events_key_press*)(list->content))->keycode == keycode)
		{
			return (char)(((t_me_events_key_press*)(list->content))
			->is_pressed);
		}
		list = list->next;
	}
	return (0);
}
