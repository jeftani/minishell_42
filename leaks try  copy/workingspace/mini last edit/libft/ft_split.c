/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:03:24 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/27 20:25:59 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../minishell.h"

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != c && (i == 0 || s[i - 1] == c))
				count++;
			i++;
		}
	}
	return (count);
}

void	ft_free(char **t, int n)
{
	int	i;

	i = 0;
	if (t[i] == NULL)
	{
		while (i < n)
		{
			free(t[i]);
			i++;
		}
		free(t);
	}
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		i;
	int		start;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	tab = (char **)ft_malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (j < ft_count_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		tab[j] = ft_substr(s, start, i - start);
		ft_free(tab, j);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
