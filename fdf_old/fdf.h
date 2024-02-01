/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:00:54 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/01 17:23:29 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include<stdio.h>
# include<fcntl.h>
# include<sys/types.h>
# include<sys/stat.h>
# include<unistd.h>
# include<stdbool.h>
# include<stdlib.h>
# include<mlx.h>
# include<math.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

# include "get_next_line.h"

//#include "libft/libft.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_fdf
{
	int	width;
	int height;
	int **z_matrix;
	int zoom;
	int z_zoom;
	int color;
	int color_delta;
	double angle;
	int isometric;
	int x_shift;
	int y_shift;
	int win_width;
	int win_height;
	int legend_offset;

	void	*mlx_ptr;
	void	*win_ptr;
	int		img_side;
	t_data	image;
}	t_fdf;

typedef struct s_bres_param
{
	int x0;
	int x1;
	int xstart;
	int y0;
	int y1;
	int ystart;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
} t_bres_param;

int	deal_key(int key, void *data);
int	get_height(char *file_name);
int	get_width(char *file_name);
bool	fill_matrix(int *z_line, char *line);
bool	read_file(char *file_name, t_fdf *data);
void	free_matrix(int **z_matrix);
t_fdf	*creat_matrix(char *file_name, t_fdf *data);
char	**ft_split(char const *s, char c); //include from libft
int	ft_atoi(const char *nptr); // add from libft
int	ft_wdcount(char const *s, char c); //include to libft
void bresenham(t_bres_param *params, t_fdf *data);
void	draw(t_fdf *data);
void    legend(t_fdf *data);
void drawline(float x, float y, float x1, float y1, t_fdf *data);
void	isometric(int *x, int *y, int z, t_fdf *data);
void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1);
void init_data(t_fdf *data);
void	img_pix_put(t_fdf *data, int x, int y, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_rectangle(t_fdf *data, int x0, int y0, int width, int height, int color);

void clear_window(t_fdf *data);
void	key_event(int keycode, t_fdf *data);

#endif
