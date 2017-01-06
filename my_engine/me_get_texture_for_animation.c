/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_get_texture_for_animation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 12:08:54 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/18 12:09:33 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		me_get_texture_for_animation(t_me_animation *animation)
{
	return (animation->current_frame + animation->first_texture_id);
}
