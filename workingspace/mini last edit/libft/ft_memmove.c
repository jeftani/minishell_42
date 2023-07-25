/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:30:54 by gloukas           #+#    #+#             */
/*   Updated: 2023/02/27 18:10:19 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, int n)
{
	int	i;

	if (!src && !dst)
		return (NULL);
	i = 0;
	if (dst > src)
	{
		while (n--)
		{
			((char *)dst)[n] = ((char *)src)[n];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
