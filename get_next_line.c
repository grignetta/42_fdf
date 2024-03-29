/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:03:02 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/02 22:04:42 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*del_buf_return_res(char **buffer, char *res, int len_to_del)
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
		return (free(res), my_free(buffer), NULL);
	i = 0;
	while ((*buffer)[len_to_del])
		new_buffer[i++] = (*buffer)[len_to_del++];
	new_buffer[i] = '\0';
	my_free(buffer);
	*buffer = new_buffer;
	return (res);
}

char	*extract_til_nl_or_end(char **buff)
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
		return (my_free(buff), NULL);
	j = 0;
	while (j < i)
	{
		res[j] = (*buff)[j];
		j++;
	}
	res[j] = '\0';
	return (del_buf_return_res(buff, res, i));
}

char	*read_buff_size(int fd, char **buffer)
{
	int		read_bytes;
	char	*temp;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (my_free(buffer), NULL);
	read_bytes = read(fd, temp, BUFFER_SIZE);
	if (read_bytes == 0)
		return (free(temp), NULL);
	if (read_bytes < 0)
		return (free(temp), my_free(buffer), NULL);
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

char	*get_next_line(int fd)
{
	static char	*buff[4096];
	char		*read_bytes;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (check_nl(buff[fd]))
			return (extract_til_nl_or_end(&buff[fd]));
		read_bytes = read_buff_size(fd, &buff[fd]);
		if (!read_bytes && buff[fd])
			return (extract_til_nl_or_end(&buff[fd]));
		else if (!read_bytes)
			return (NULL);
		buff[fd] = ft_strjoin_gnl(buff[fd], read_bytes);
	}
}
