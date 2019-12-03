/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_try.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:19:09 by antmarti          #+#    #+#             */
/*   Updated: 2019/12/02 12:26:34 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	char		buffer[4096];
	int			ret;
	
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (*line == 0)
			*line = ft_strdup(buffer);
		else 
			*line = ft_strjoin(*line, buffer);
		return (1);
	}
	return (0);	
}

int main()
{
	char	*line;
	int 	fd;

	fd = open("prueba.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}
