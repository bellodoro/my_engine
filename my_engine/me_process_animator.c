/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_process_animator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 11:23:39 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/19 13:10:55 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

void	me_process_animator(t_me_animator *animator, t_me_ms delta_time)
{
	animator->value += animator->amount_every_seconds * delta_time / 1000;
	animator->amount_every_seconds += animator->velocity * delta_time / 1000;
	if (animator->amount_every_seconds < animator->delta_min)
		animator->amount_every_seconds = animator->delta_min;
	else if (animator->amount_every_seconds > animator->delta_max)
		animator->amount_every_seconds = animator->delta_max;
}
