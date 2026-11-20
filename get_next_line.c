/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 10:46:15 by tdefeche          #+#    #+#             */
/*   Updated: 2026/11/18 11:46:18 by tdefeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line.h"

int	ft_index_of(const char *s, int c)
{
	int	index;

	index = 0;
	if (!s)
		return (-1);
	while (1 == 1)
	{
		if (s[index] == (char)c)
			return (index);
		if (s[index] == '\0')
			break ;
		index++;
	}
	return (-1);
}

static char *append(char *acc, const char *buf, size_t *len, size_t *cap)
{
  char    *bigger;
  size_t  n;

  n = ft_strlen(buf);
  if (*len + n + 1 > *cap)
  {
    *cap = (*len + n + 1) * 2;
    bigger = (char *)malloc(*cap);
    if (!bigger)
    {
      free(acc);
      return (NULL);
    }
    ft_memcpy(bigger, acc, *len);
    free(acc);
    acc = bigger;
  }
  ft_memcpy(acc + *len, buf, n);
  *len += n;
  acc[*len] = '\0';
  return (acc);
}

char	*fill_buffer(char *buffer, char *stash, int fd)
{
  size_t  len;
  size_t  cap;
  int     byte_read;

  if (ft_strchr(stash, '\n'))
      return (stash);
  len = ft_strlen(stash);
  cap = 0;
  if (stash)
    cap = len + 1;
  byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[byte_read] = '\0';
    stash = append(stash, buffer, &len, &cap);
    if (!stash || ft_strchr(buffer, '\n'))
      break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			end;
	char		*line;
	char		*tmp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = fill_buffer(buffer, stash, fd);
	free(buffer);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	end = ft_index_of(stash, '\n');
	if (end == -1)
		end = ft_strlen(stash) - 1;
	line = ft_substr(stash, 0, end + 1);
	tmp = ft_substr(stash, end + 1, ft_strlen(stash));
	free(stash);
	stash = tmp;
	return (line);
}
