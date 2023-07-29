/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:38:55 by gloukas           #+#    #+#             */
/*   Updated: 2023/02/27 18:08:51 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int find)
{
	int	i;

	i = ft_strlen(s);
	if ((char)find == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
		s++;
	s--;
	while (i)
	{
		if (*s == (char)find)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}
