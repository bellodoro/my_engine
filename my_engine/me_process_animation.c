/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 11:46:42 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/18 12:23:10 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"
#include "stdio.h"

void	me_process_animation(t_me_animation *animation, t_me_ms delta_time)
{
	animation->time_of_last_frame += delta_time;
	if (animation->time_of_last_frame >= animation->millis_between_frames)
	{
		animation->time_of_last_frame = 0;
		++animation->current_frame;
		if (animation->current_frame == animation->number_of_frame)
			animation->current_frame = 0;
	}
}
