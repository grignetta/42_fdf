/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:20:29 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/02 21:51:51 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	height = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	int	width;
	int	fd;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	width = ft_wdcount(line, ' ');
	free(line);
	close(fd);
	return(width);
}

int	ft_wdcount(char const *s, char c) // include to libft
{
	long unsigned int	i;
	int					count;
	int					word;

	i = 0;
	word = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			if (word == 0)
			{
				count++;
				word = 1;
			}
		}
		else
			word = 0;
		i++;
	}
	return (count);
}
/*
int	ft_atoi(const char *nptr) // add from libft
{
	int	i;
	int	count;
	int	number;

	i = 0;
	count = 0;
	number = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			count = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	if ((count % 2) == 1)
		return (-1 * number);
	return (number);
}
*/
t_fdf	*creat_matrix(char *file_name, t_fdf *data)
{
	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->z_matrix = (int **)malloc(sizeof(int*) * (data->height + 1));
	if (!data->z_matrix)
		return (NULL);
	int i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (data->width + 2));
		if (!data->z_matrix[i])
		{
			free_matrix(data->z_matrix);
			return (NULL);
		}
		i++;
	}
	data->z_matrix[i] = NULL;
	return(data);
}

bool	read_file(char *file_name, t_fdf *data)
{
	int	fd;
	char	*line;
	int i;

	i = 0;
	data->height = get_height(file_name);
	if(!creat_matrix(file_name, data))
		return (true);
	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (free_matrix(data->z_matrix), true);
	while (i < data->height)
	{
		line = get_next_line(fd);
		if (!line)
			return(free_matrix(data->z_matrix), close(fd), true);
		if(fill_matrix(data->z_matrix[i++], line))
			return(free_matrix(data->z_matrix), close(fd), true);
		free(line);
	}
	close(fd);
	//data->z_matrix[i] = NULL;
	return (false);
}

bool	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int	i;
	//int count;

	//count = ft_wdcount(line, ' ');
	nums = ft_split(line, ' ');
	if (!nums)
		return (true);
	i = 0;
	while (nums[i])// && --count)
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	z_line[i] = 0;
	return(free(nums), false);
}

void	free_matrix(int **z_matrix)
{
	int	i;

	i = 0;
	if (z_matrix == NULL)
		return ;
	while (z_matrix[i])
		free(z_matrix[i++]);
	free(z_matrix);
	return ;
}
