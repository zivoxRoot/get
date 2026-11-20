/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:12:38 by tdefeche          #+#    #+#             */
/*   Updated: 2026/11/18 11:46:28 by tdefeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < n)
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_s1;
	int		size_s2;
	char	*res;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	res = (char *)malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, size_s1);
	ft_memcpy(res + size_s1, s2, size_s2);
	res[size_s1 + size_s2] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	if (!s)
		return (NULL);
	while (1 == 1)
	{
		if (s[index] == (char)c)
			return ((char *)&(s[index]));
		if (s[index] == '\0')
			break ;
		index++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
