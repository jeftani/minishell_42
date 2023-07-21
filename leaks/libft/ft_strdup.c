/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 05:18:42 by gloukas           #+#    #+#             */
/*   Updated: 2022/12/12 21:01:50 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*t;

	t = malloc(ft_strlen(src) + 1);
	if (!t)
		return (NULL);
	ft_strlcpy(t, src, ft_strlen(src) + 1);
	return (t);
}
