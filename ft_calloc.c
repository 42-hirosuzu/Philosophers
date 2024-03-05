/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 06:43:30 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/02/27 01:29:17 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*chr;

	chr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		chr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	mallocsize;

	if (size != 0 && (size_t)SIZE_MAX / size < count)
		return (NULL);
	if (count == 0 || size == 0)
		mallocsize = 1;
	else
		mallocsize = count * size;
	p = (void *)malloc(mallocsize);
	if (!p)
		return (NULL);
	ft_bzero(p, mallocsize);
	return (p);
}
