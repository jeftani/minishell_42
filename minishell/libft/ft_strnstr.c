/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 07:58:32 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/09 05:35:25 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int	i;
	int	j;
	if(!str)
		return(0);
	if (to_find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j])
		{
			if (to_find[j + 1] == '\0' && i + j < len)
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
