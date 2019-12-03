/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:01:25 by antmarti          #+#    #+#             */
/*   Updated: 2019/12/03 19:23:22 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	int			ret;
	char		buffer[BUFFER_SIZE + 1];
	static char	*file[4096];
	char		*acc;
	
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strdup(buffer);
		else 
		{
			acc = ft_strjoin(file[fd], buffer);
			free (file[fd]);
			file[fd] = acc;
		}
		if (ft_strchr(file[fd], '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{	
		if (file[fd])
		{
			//printf("%s\n", file[fd]);
			*line = ft_strdup(file[fd]);
			free(file[fd]);
			file[fd] = 0;
		}
		else
			*line = ft_strdup("");
		return (0);
	}
	return (ft_checker(fd, line, file));	
}

int		ft_checker(int fd, char **line, char **file)
{
	int		i;
	char	*temp;

	i = 0;
	
	while (file[fd][i] && file[fd][i] != '\n')
		i++;
	if (file[fd][i] == '\n')
	{
		*line = ft_substr(file[fd], 0, i);
		temp = ft_strdup(&((file[fd])[i + 1]));
		free (file[fd]);
		file[fd] = temp;
		
	}
	return (1);
}

int main()
{
        int             fd;
        int             i;
        int             j;
        char                    *line = 0;
       // char                    *lineadress[66];

        j = 1;
        printf("\n==========================================\n");
        printf("========= TEST 5 : Four New Lines ========\n");
        printf("==========================================\n\n");

        if (!(fd = open("42TESTERS-GNL/files/4_newlines", O_RDONLY)))
        {
                printf("\nError in open\n");
                return (0);
        }
        while ((i = get_next_line(fd, &line)) > 0)
        {
                printf("|%s\n", line);
                free(line);
                j++;
        }
        printf("|%s\n", line);
        free(line);
        close(fd);

        if (i == -1)
                printf ("\nError in Fonction - Returned -1\n");
        else if (j == 5)
                printf("\nRight number of lines\n");
        else if (j != 5)
                printf("\nNot Good - Wrong Number Of Lines\n");
}