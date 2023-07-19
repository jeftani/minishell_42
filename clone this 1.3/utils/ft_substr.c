/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:49:08 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/13 03:52:49 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (0);
	if (len >= ft_strlen1(s) - start)
		len = ft_strlen1(s) - start;
	i = start;
	j = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (s[i] && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
