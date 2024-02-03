/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:37:34 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 16:03:18 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_color(t_fdf *data, int z)
{
	if (data->black == 0)
	{
		if (z != 0)
			data->color = 0xff00ff;
		else
			data->color = 0x0fffff;
	}
	else if (data->black == 1)
	{
		if (z != 0)
			data->color = 0xffffff;
		else
			data->color = 0x444444;
	}
	return ;
}

double	distance(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void	update_color(t_bres_param *params, t_fdf *data, int z, int z1)
{
	union u_color	c;
	double			current_distance;
	double			full_distance;

	current_distance = distance(params->xstart, params->ystart, params->x0,
			params->y0);
	full_distance = sqrt((params->y1 - params->ystart)
			* (params->y1 - params->ystart) + (params->x1 - params->xstart)
			* (params->x1 - params->xstart));
	current_distance /= full_distance;
	c.color = data->color;
	if (data->black == 0)
		not_black_color(&c, z, z1, current_distance);
	else
		black_color(&c, z, z1, current_distance);
	data->color = c.color;
}

void	not_black_color(union u_color *c, int z, int z1,
		double current_distance)
{
	if (z1 != 0 && z == 0)
	{
		c->values[1] = 0x00 - 0xff * current_distance;
		c->values[2] = 0xff + 0xf0 * current_distance;
	}
	if (z1 == 0 && z != 0)
	{
		c->values[1] = 0x00 + 0xff * current_distance;
		c->values[2] = 0xff - 0xf0 * current_distance;
	}
}

void	black_color(union u_color *c, int z, int z1, double current_distance)
{
	if (z1 != 0 && z == 0)
	{
		c->values[0] = 0x44 + 0xbb * current_distance;
		c->values[1] = 0x44 + 0xbb * current_distance;
		c->values[2] = 0x44 + 0xbb * current_distance;
	}
	if (z1 == 0 && z != 0)
	{
		c->values[0] = 0xff - 0xbb * current_distance;
		c->values[1] = 0xff - 0xbb * current_distance;
		c->values[2] = 0xff - 0xbb * current_distance;
	}
}
