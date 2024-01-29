/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:49:25 by dpadenko          #+#    #+#             */
/*   Updated: 2024/01/29 21:09:48 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void *data)
{
	printf("%d", key);
	return (0);
}

int	handle_input(int keycode, t_fdf *data)
{
	if (keycode == 65307) // 53 is the keycode for the ESC key
	{
		printf("The %d key (ESC) has been pressed\n\n", keycode);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("The %d key has been pressed\n\n", keycode);
	return(0);
}

int	main(int argc, char **argv)
{
	t_fdf *data;

	data = (t_fdf*)malloc(sizeof(t_fdf));
	if (read_file(argv[1], data))
		return (0);
	printf("height %d", data->height);
	printf("weight %d", data->width);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		return (0);
	}
	//bresenham(10, 10, 600, 300, data);
	data->zoom = 50;
	draw(data);
	//mlx_key_hook(data->win_ptr, deal_key, NULL);
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_loop(data->mlx_ptr);
	//mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	//free(data->mlx_ptr);
}

/*
int	main(int argc, char **argv)
{
	t_fdf	data;

	if (read_file(argv[1], &data))
		return(0);
	int i;
	int j;

	i = 0;
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
		{
			printf("%3d ", data.z_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}*/