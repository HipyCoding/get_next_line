/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: candrese <candrese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:48:46 by candrese          #+#    #+#             */
/*   Updated: 2024/02/26 17:13:33 by candrese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read(int fd, char *safe)
{
	int		check;
	char	*buffer;

	check = 1;
	buffer = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free (safe);
		return (NULL);
	}
	while (check && !ft_strchr(safe, '\n'))
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
		{
			free (buffer);
			free (safe);
			return (NULL);
		}
		buffer[check] = '\0';
		safe = ft_strjoin(safe, buffer);
	}
	free (buffer);
	return (safe);
}

static char	*ft_next(char **stash)
{
	char	*p;
	char	*line;

	p = stash[0];
	while (*p && *p != '\n')
		p++;
	if (*p == '\n')
		p++;
	line = ft_substr(stash[0], 0, (size_t)(p - *stash));
	if (!line)
	{
		free (*stash);
		return (NULL);
	}
	p = ft_substr(&p[0], 0, ft_strlen(p));
	if (!p)
	{
		free (*stash);
		return (NULL);
	}
	free (*stash);
	*stash = p;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*safe[1024];
	char			*ret;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	if (!safe[fd])
		safe[fd] = ft_strdup("");
	if (!safe[fd])
		return (NULL);
	safe[fd] = ft_read (fd, safe[fd]);
	if (!safe[fd] || !*safe[fd])
	{
		free (safe[fd]);
		safe[fd] = NULL;
		return (NULL);
	}
	ret = ft_next(&safe[fd]);
	return (ret);
}
