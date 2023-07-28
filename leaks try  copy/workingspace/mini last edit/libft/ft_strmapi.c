/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:03:48 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/27 23:37:25 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../minishell.h"

char	*ft_strmapi(char *s, char (*f)(int, char))
{
	char	*p;
	int		i;

	if (s == 0 || f == 0)
		return (NULL);
	i = 0;
	p = (char *)ft_malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
