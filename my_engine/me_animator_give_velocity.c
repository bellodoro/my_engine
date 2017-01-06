/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_animator_give_velocity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 11:22:28 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/19 13:12:42 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

void	me_animator_give_velocity(t_me_animator *animator, double velocity)
{
	animator->amount_every_seconds += velocity;
}
