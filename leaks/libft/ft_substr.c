/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:22:56 by gloukas           #+#    #+#             */
/*   Updated: 2023/02/27 18:07:40 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*funct(char *s, int i, char *p, int len)
{
	int	j;

	j = 0;
	while (s[i])
	{
		if (j < len)
		{
			p[j] = *((char *)(s + i));
			j++;
		}
		i++;
	}
	p[j] = '\0';
	return (p);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len + start > ft_strlen(s))
		p = (char *)malloc(ft_strlen(s) - start + 1);
	else
		p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	i = start;
	return (funct(s, i, p, len));
}
