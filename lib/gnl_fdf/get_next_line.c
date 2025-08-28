/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:03:02 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/05 19:54:14 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*del_buf_return_res(char **buffer, char *res,
		int len_to_del, t_fdf *data)
{
	int		new_len;
	int		i;
	char	*new_buffer;

	i = len_to_del;
	new_len = 0;
	while ((*buffer)[i++])
		new_len++;
	if (new_len == 0)
		return (my_free(buffer), res);
	new_buffer = (char *)malloc(new_len + 1);
	if (!new_buffer)
		return (free(res), free_and_exit(buffer, data), NULL);
	i = 0;
	while ((*buffer)[len_to_del])
		new_buffer[i++] = (*buffer)[len_to_del++];
	new_buffer[i] = '\0';
	my_free(buffer);
	*buffer = new_buffer;
	return (res);
}

char	*extract_til_nl_or_end(char **buff, t_fdf *data)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if (!*buff)
		return (NULL);
	while ((*buff) && (*buff)[i])
	{
		if ((*buff)[i++] == '\n')
			break ;
	}
	res = (char *)malloc(i + 1);
	if (!res)
		return (free_and_exit(buff, data), NULL);
	j = 0;
	while (j < i)
	{
		res[j] = (*buff)[j];
		j++;
	}
	res[j] = '\0';
	return (del_buf_return_res(buff, res, i, data));
}

char	*read_buff_size(int fd, char **buffer, t_fdf *data)
{
	int		read_bytes;
	char	*temp;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free_and_exit(buffer, data), NULL);
	read_bytes = read(fd, temp, BUFFER_SIZE);
	if (read_bytes == 0)
		return (free(temp), NULL);
	if (read_bytes < 0)
		return (free(temp), free_and_exit(buffer, data), NULL);
	temp[read_bytes] = '\0';
	return (temp);
}

int	check_nl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd, t_fdf *data)
{
	static char	*buff;
	char		*read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_exit(&buff, data), NULL);
	while (1)
	{
		if (check_nl(buff))
			return (extract_til_nl_or_end(&buff, data));
		read_bytes = read_buff_size(fd, &buff, data);
		if (!read_bytes && buff)
			return (extract_til_nl_or_end(&buff, data));
		else if (!read_bytes)
			return (NULL);
		buff = ft_strjoin_gnl(buff, read_bytes, data);
	}
}
