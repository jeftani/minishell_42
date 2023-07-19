/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:49:45 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/13 03:52:38 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = -1;
	dup = malloc(sizeof(char) * (ft_strlen1(str) + 1));
	if (!dup)
	{
		free(dup);
		return (NULL);
	}
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}
