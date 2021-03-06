/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:48 by akhastaf          #+#    #+#             */
/*   Updated: 2020/11/24 14:01:57 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
void    readline()
{   
    get_next_line(0, &g_line);
}
char	*ft_checkerror(int fd, char **buff)
{
	if (!(BUFFER_SIZE >= 1) || (read(fd, *buff, 0) < 0))
		return (NULL);
	return (*buff);
}

int		ft_readline(int fd, char **str)
{
	char	*tmp;
	char	*buff;
	int		n;

	if ((!(buff = malloc(BUFFER_SIZE + 1))) || (!ft_checkerror(fd, &buff)))
	{
		free(buff);
		return (-1);
	}
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buff);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	free(buff);
	return (n);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[ULIMIT];
	char		*tmp;
	char		*s;
	int			n;

	if ((n = ft_readline(fd, &str[fd]) < 0 || !line))
		return (-1);
	if ((s = ft_strchr(str[fd], '\n')))
	{
		*line = ft_strndup(str[fd], s - str[fd]);
		tmp = str[fd];
		str[fd] = ft_strdup(s + 1);
		free(tmp);
		return (1);
	}
	if (!n && str[fd])
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}