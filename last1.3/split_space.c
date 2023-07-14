/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:41:16 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/14 08:14:35 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_split_help(char *cmd_line, t_splity *s)
{
	s->tab = (char *)malloc((ft_strlen(cmd_line) + 1) * sizeof(char));
	printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, s->tab);
	if (!(s->tab))
		return ;
	s->i = -1;
	while (cmd_line[++(s->i)])
	{
		if (cmd_line[s->i] == ' ' && !is_inside_quotes(cmd_line, s->i)
			&& !is_inside_single_quotes(cmd_line, s->i))
			s->tab[s->i] = '1';
		else
			s->tab[s->i] = '2';
	}
	s->tab[s->i] = '\0';
	s->i = -1;
	s->count = 0;
	while (s->tab[++(s->i)])
		if (s->tab[s->i] == '2' && (s->i == 0 || s->tab[s->i - 1] == '1'))
			(s->count)++;
}

char	**arg_split(char *cmd_line)
{
	t_splity	s;

	arg_split_help(cmd_line, &s);
	s.res = (char **)malloc((s.count + 1) * sizeof(char *));
	printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, s.res);
	if (!(s.res))
	{
		free(s.tab);
		return (NULL);
	}
	s.j = -1;
	s.i = 0;
	while (++(s.j) < s.count)
	{
		while (cmd_line[s.i] && s.tab[s.i] == '1')
			(s.i)++;
		s.start = s.i;
		while (cmd_line[s.i] && s.tab[s.i] == '2')
			(s.i)++;
		s.res[s.j] = ft_substr(cmd_line, s.start, s.i - s.start);
		ft_free(s.res, s.j);
	}
	s.res[s.j] = NULL;
	free(s.tab);
	return (s.res);
}
