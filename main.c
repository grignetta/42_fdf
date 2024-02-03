/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:49:25 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 15:30:07 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_data(t_fdf *data)
{
	data->zoom = 10;
	data->z_zoom = 8;
	data->angle = 0.523598;
	data->isometric = 0;
	data->x_shift = 200;
	data->y_shift = 200;
	data->win_width = 1000;
	data->win_height = 1000;
	data->legend_offset = 120;
	data->black = 1;
}

t_fdf	*initialize_matrix(char *filename)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (read_file(filename, data))
		return (NULL);
	init_data(data);
	return (data);
}

int	initialize_graphics(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width,
			data->win_height,
			"FDF");
	if (data->win_ptr == NULL)
		return (1);
	return (0);
}

int	initialize_image(t_fdf *data)
{
	data->image.img = mlx_new_image(data->mlx_ptr,
			data->win_height,
			data->win_width);
	if (data->image.img == NULL)
		return (1);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel,
			&data->image.line_length,
			&data->image.endian);
	if (data->image.addr == NULL)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc > 1)
	{
		data = initialize_matrix(argv[1]);
		if (data == NULL)
			return (1);
		if (initialize_graphics(data))
			return (free_matrix(data->z_matrix), free(data), 1);
		if (initialize_image(data))
			return (free(data->win_ptr), mlx_destroy_display(data->mlx_ptr),
				free_matrix(data->z_matrix), free(data), 1);
		draw(data);
		mlx_mouse_hook(data->win_ptr, mouse_event, data);
		mlx_hook(data->win_ptr, 2, 1, handle_input, data);
		mlx_hook(data->win_ptr, 17, 0, close_event, data);
		mlx_loop_hook(data->mlx_ptr, update, data);
		mlx_loop(data->mlx_ptr);
	}
}
