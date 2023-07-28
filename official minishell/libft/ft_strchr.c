/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:18:53 by gloukas           #+#    #+#             */
/*   Updated: 2022/12/23 03:55:50 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int find)
{
	if ((char)find == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (*((char *)s))
	{
		if (*((char *)s) == (char)find)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
