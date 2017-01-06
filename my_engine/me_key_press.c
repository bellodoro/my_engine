/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:48:38 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/05 11:47:48 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		me_key_press(int keycode, void *param)
{
	t_me_engine				*engine;
	t_list					*list;
	t_me_events_key_press	key;

	engine = (t_me_engine*)param;
	list = engine->events.key_pressed;
	while (list)
	{
		if (((t_me_events_key_press*)(list->content))->keycode == keycode)
		{
			((t_me_events_key_press*)(list->content))->is_pressed = 1;
			return (1);
		}
		list = list->next;
	}
	key.keycode = keycode;
	key.is_pressed = 1;
	ft_lstadd(&engine->events.key_pressed, ft_lstnew(&key,
				sizeof(t_me_events_key_press)));
	return (0);
}
