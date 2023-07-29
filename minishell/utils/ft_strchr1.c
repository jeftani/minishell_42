/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:15:19 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/13 03:50:56 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_strchr1(char const *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen1(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_strchr2(char const *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen1(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strchrr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (str[i] != (char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i);
}
