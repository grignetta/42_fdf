/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:00:54 by dpadenko          #+#    #+#             */
/*   Updated: 2023/12/19 19:04:50 by dpadenko         ###   ########.fr       */
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

# include "get_next_line.h"

//#include "libft/libft.h"

typedef struct s_fdf
{
	int	width;
	int height;
	int **z_matrix;
	int zoom;
	int color;

	void	*mlx_ptr;
	void	*win_ptr;
}	t_fdf;

typedef struct s_draw_fdf
{
	float x;
	float y;
	float x1;
	float y1;
	t_fdf *data;
} t_draw_fdf;

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
void	bresenham(float x, float y, float x1, float y1, t_fdf *data);
void	draw(t_fdf *data);
void	isometric(float *x, float *y, int z);

#endif
