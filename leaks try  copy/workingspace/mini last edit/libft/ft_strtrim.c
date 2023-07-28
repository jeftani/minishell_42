/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:03:59 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/27 23:37:30 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*t;

	t = 0;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		t = (char *)ft_malloc(sizeof(char) * (end - start + 1));
		if (t)
			ft_strlcpy(t, &s1[start], end - start + 1);
	}
	return (t);
}
