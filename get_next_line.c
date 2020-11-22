/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellacroi <ellacroi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:51:16 by ellacroi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/22 21:17:52 by ellacroi         ###   ########.fr       */
=======
/*   Updated: 2020/11/22 21:39:52 by ellacroi         ###   ########.fr       */
>>>>>>> f0dac41a833d1dc6af058eb1d3b6c48f9b765a0b
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

<<<<<<< HEAD
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
=======
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
//#define BUFFER_SIZE 4
>>>>>>> f0dac41a833d1dc6af058eb1d3b6c48f9b765a0b

int	ft_remove_line_from_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n' && i <BUFFER_SIZE)
		i++;
	if (buffer[i] == '\0')
		return (0);
	while (++i < BUFFER_SIZE)
		buffer[j++] = buffer[i];
	while (j < BUFFER_SIZE)
		buffer[j++] = '\0';
	return (1);
}

int	ft_buffer_to_line(char *buffer, char **line)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n' && i <BUFFER_SIZE)
		i++;
	while (*line && (*line)[j])
		j++;
	if (!(newline = malloc(sizeof(char) * (i + j + 1))))
		return (-1);
	newline[i + j] = '\0';
	while (i--)
		newline[j + i] = buffer[i];
	while (j--)
		newline[j] = (*line)[j];
	if (*line)
		free(*line);
	*line = newline;
	return(ft_remove_line_from_buffer(buffer));
}

int	get_next_line(int fd, char **line)
{
<<<<<<< HEAD
	static char	buffer[BUFFER_SIZE];
=======
	static char	buffer[BUFFER_SIZE + 1];
>>>>>>> f0dac41a833d1dc6af058eb1d3b6c48f9b765a0b
	int			ret;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	ret = 0;
	while ((ret = ft_buffer_to_line(buffer, line)) == 0)
	{
		if ((ret = read(fd, buffer, BUFFER_SIZE)) < 1)
		{
			if (ret == -1)
			{
				if (*line)
					free(*line);
				line = NULL;
			}
			return (ret);
		}
	}
	return (ret);
}
<<<<<<< HEAD
/*
=======

>>>>>>> f0dac41a833d1dc6af058eb1d3b6c48f9b765a0b
int	main(int ac, char **av)
{
	(void)ac;
	int	fd = open(av[1], O_RDONLY);
<<<<<<< HEAD
	int	fd2 = open(av[2], O_RDONLY);
	char *line = NULL;

	get_next_line(fd, &line);
	get_next_line(fd, &line);
	get_next_line(fd2, &line);
	printf("line = %s\n", line);
}*/
=======
	char *line = NULL;

	get_next_line(fd, &line);
	printf("line = %s\n", line);
	get_next_line(fd, &line);
	printf("line = %s\n", line);
	get_next_line(fd, &line);
	printf("line = %s\n", line);
}
>>>>>>> f0dac41a833d1dc6af058eb1d3b6c48f9b765a0b
