/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_thing_combsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:23:02 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 14:23:46 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

static int		me_thing_combsort2(int amount,
		int gap, int *order, double *dist)
{
	double	d;
	int		i;
	int		j;
	int		o;
	int		swapped;

	i = 0;
	swapped = 0;
	while (i < amount - gap)
	{
		j = i + gap;
		if (dist[i] < dist[j])
		{
			d = dist[i];
			dist[i] = dist[j];
			dist[j] = d;
			o = order[i];
			order[i] = order[j];
			order[j] = o;
			swapped = 1;
		}
		++i;
	}
	return (swapped ? 1 : 0);
}

void			me_thing_combsort(int *order, double *dist, int amount)
{
	int		gap;
	int		swapped;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped != 0)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		if (me_thing_combsort2(amount, gap, order, dist))
			swapped = 1;
	}
}
