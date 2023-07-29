/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:39:00 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 16:16:52 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;

	if (!s1 || !s2)
		return (NULL);
	new_s = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_s, s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return (new_s);
}
