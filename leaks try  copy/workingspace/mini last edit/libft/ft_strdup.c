/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 05:18:42 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/27 23:37:14 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../minishell.h"

char	*ft_strdup(char *src)
{
	char	*t;

	t = ft_malloc(ft_strlen(src) + 1);
	if (!t)
		return (NULL);
	ft_strlcpy(t, src, ft_strlen(src) + 1);
	return (t);
}
