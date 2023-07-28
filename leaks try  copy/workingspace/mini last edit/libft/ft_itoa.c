/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:02:29 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 00:59:41 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

static int	ft_lenght(int n)
{
	if (n <= 0)
		return (1);
	else
		return (0);
}

static char	ft_start(long n)
{
	if (n < 0)
		return ('-');
	else
		return ('0');
}

static long	ft_put(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	tmp;
	int		length;

	tmp = (long)n;
	length = ft_lenght(n);
	while (n)
	{
		n /= 10;
		length++;
	}
	str = (char *)ft_malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (tmp <= 0)
		str[0] = ft_start(tmp);
	while (tmp)
	{
		str[--length] = ft_put(tmp) % 10 + '0';
		tmp /= 10;
	}
	return (str);
}
