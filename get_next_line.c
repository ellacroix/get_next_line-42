/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellacroi <ellacroi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:51:16 by ellacroi          #+#    #+#             */
/*   Updated: 2020/11/23 10:56:06 by ellacroi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
//#define BUFFER_SIZE 2

int	ft_remove_line_from_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		buffer[i] = '\0';
		i++;
	}
	if (buffer[i] == '\0')		//Verifie si buffer contient une line (\n), sinon renvoie 0 pour read plus de caracteres
		return (0);
	while (++i < BUFFER_SIZE)	//buffer contient un \n, on decale buffer vers la gauche pour effacer la line envoyee + le \n ("ab\n01" -> "01")
		buffer[j++] = buffer[i];
	while (j < BUFFER_SIZE)		//on efface les derniers caracteres
		buffer[j++] = '\0';
	return (1);					//Porte de sortie indiquant une line complete dans line
}

int	ft_buffer_to_line(char *buffer, char **line)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')	//On lit buffer jusqu'a sa fin ou un \n, i < BUFFER_SIZE inutile ?
		i++;
	while (*line && (*line)[j])	//Si line contient quelque chose, on le mesure
		j++;
	if (!(newline = malloc(sizeof(char) * (i + j + 1))))	//malloc pouvant accueillir buffer + line + \0
		return (-1);
	newline[i + j] = '\0';
	while (i--)					//Copie le buffer au bout de newline, depuis la fin
		newline[j + i] = buffer[i];
	while (j--)					//Copie ce qu'il y avait dans line, depuis la fin
		newline[j] = (*line)[j];
	if (*line)					//Libere l'ancienne line, si de la memoire lui etait allouee (donc chaque passage sauf premier appel)
		free(*line);
	*line = newline;
	return(ft_remove_line_from_buffer(buffer));
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			ret;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	*line = NULL;	//On reset line si elle contient quelque chose d'un appel precedent
	ret = 0;
	while ((ret = ft_buffer_to_line(buffer, line)) == 0) //si ret == 0, line pas fini, si ret == 1, line fini
	{
		if ((ret = read(fd, buffer, BUFFER_SIZE)) < 1)
		{
			if (ret == -1)
			{
				if (*line)
					free(*line);
				line = NULL;
			}			
			return (ret);	//Porte de sortie en cas d'atteinte de EOF, ret == 0 (ou d'erreur de read, ret == -1)
		}
	}
	return (ret);
}

/*
int	main(int ac, char **av)
{
	(void)ac;
	int	fd = open(av[1], O_RDONLY);
	char *line;
	int ret = 1;

	printf("fd = %d\n", fd);
	while (ret > 0)
	{
		printf("return: %d \t ",ret = get_next_line(fd, &line));
		printf("line = %s\n", line);
	}
}
*/