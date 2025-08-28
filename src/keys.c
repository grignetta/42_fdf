/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:20:13 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/04 16:46:06 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keycode, t_fdf *data)
{
	if (keycode == 65362 || keycode == 65364 || keycode == 65361
		|| keycode == 65363 || keycode == 99 || keycode == 97 || keycode == 105
		|| keycode == 111 || keycode == 117 || keycode == 100 || keycode == 115)
		key_event(keycode, data);
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx_ptr, data->image.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free_matrix(data->z_matrix);
		free(data);
		exit(1);
	}
	return (0);
}

void	key_event(int keycode, t_fdf *data)
{
	if (keycode == 65364)
		data->y_shift += 10;
	if (keycode == 65362)
		data->y_shift += -10;
	if (keycode == 65361)
		data->x_shift += -10;
	if (keycode == 65363)
		data->x_shift += 10;
	if (keycode == 105)
		data->zoom += 5;
	if (keycode == 111)
	{
		if (data->zoom >= 5)
			data->zoom -= 5;
	}
	if (keycode == 117)
		data->z_zoom += 0.5;
	if (keycode == 100)
		data->z_zoom -= 0.5;
	if (keycode == 115)
		data->isometric = !data->isometric;
	if (keycode == 97)
		data->angle += 0.1;
	if (keycode == 99)
		data->black = !data->black;
}

int	mouse_event(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->zoom += 5;
	else if (button == 5)
	{
		if (data->zoom >= 5)
			data->zoom -= 5;
	}
	return (0);
}

int	close_event(t_fdf *data)
{
	mlx_destroy_image(data->mlx_ptr, data->image.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_matrix(data->z_matrix);
	free(data);
	exit(1);
	return (0);
}

void	clear_window(t_fdf *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->win_width)
	{
		y = 0;
		while (y < data->win_height)
			my_mlx_pixel_put(&data->image, x, y++, 0);
		x++;
	}
}
