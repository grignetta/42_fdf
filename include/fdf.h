/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:00:54 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 16:00:08 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# include "get_next_line.h"
# include "./libft/libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_fdf
{
	int		width;
	int		height;
	int		**z_matrix;
	int		zoom;
	float	z_zoom;
	int		color;
	int		black;
	int		color_delta;
	double	angle;
	int		isometric;
	int		x_shift;
	int		y_shift;
	int		win_width;
	int		win_height;
	int		legend_offset;

	void	*mlx_ptr;
	void	*win_ptr;
	int		img_side;
	t_data	image;
}	t_fdf;

typedef struct s_bres_param
{
	int	x0;
	int	x1;
	int	xstart;
	int	y0;
	int	y1;
	int	ystart;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_bres_param;

union u_color
{
	int				color;
	unsigned char	values[4];
};

//initializing matrix and reading data from a given map
t_fdf	*initialize_matrix(char *filename);
void	init_data(t_fdf *data);
bool	read_file(char *file_name, t_fdf *data);
t_fdf	*creat_matrix(char *file_name, t_fdf *data);
int		get_height(char *file_name);
int		get_width(char *file_name);
int		ft_wdcount(char const *s, char c);
bool	fill_matrix(int *z_line, char *line);

//initiolazing graphics, window and image
int		initialize_image(t_fdf *data);
int		initialize_graphics(t_fdf *data);

//error handling in the matrix and graphics creation
void	free_matrix(int **z_matrix);

//drawing image using bresenham algorithm
void	draw(t_fdf *data);
void	draw_lines(t_fdf *data);
void	bresenham(t_bres_param *params, t_fdf *data);
void	set_bres_param(t_bres_param *params);
void	draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	update_params(t_bres_param *params, int e2);

//handling isometric and colors
void	isometric(int *x, int *y, int z, t_fdf *data);
void	set_color(t_fdf *data, int z);
void	not_black_color(union u_color *c, int z, int z1,
			double currnt_distance);
void	black_color(union u_color *c, int z, int z1,
			double currnt_distance);
double	distance(double x0, double y0, double x1, double y1);
void	update_color(t_bres_param *params, t_fdf *data, int z, int z1);

//legend
void	legend(t_fdf *data);
void	draw_rectangle(t_fdf *data, int height, int color);

//events handling
void	clear_window(t_fdf *data);
void	key_event(int keycode, t_fdf *data);
int		mouse_event(int button, int x, int y, t_fdf *data);
int		close_event(t_fdf *data);
int		handle_input(int keycode, t_fdf *data);
int		update(t_fdf *data);

#endif
