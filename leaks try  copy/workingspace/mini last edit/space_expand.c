/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:10:43 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 00:58:29 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_split_help(char *cmd_line, t_splity *s)
{
	s->tab = (char *)ft_malloc((ft_strlen(cmd_line) + 1) * sizeof(char));
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
	s.res = (char **)ft_malloc((s.count + 1) * sizeof(char *));
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
		//ft_free(s.res, s.j);
	}
	s.res[s.j] = NULL;
	//free(s.tab);
	return (s.res);
}

char	*get_expanded(char *cmd_line, char *new, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*value;
	int		len;

	start = (*i) + 1;
	while (cmd_line[(*i) + 1] && (cmd_line[(*i) + 1] == '_'
			|| ft_isalnum(cmd_line[(*i) + 1])))
		(*i)++;
	len = (*i) - start + 1;
	key = malloc(len + 1);
	ft_memcpy(key, cmd_line + start, len);
	key[len] = '\0';
	value = search_env_elem2(key, env->env , env);
	if (value)
	{
		new = ft_strjoin(new, value);
	}
	else
	{
		new = ft_strjoin(new, "");
	}
	free(key);
	if(*new == ' ')
		new = ft_strtrim(new," ");
	//free();
	return (new);
}

char	*expand(char *cmd_line, t_env *env,t_lexer *lexer)
{
	int		i;
	char	*new;
	char	c[2];

	if (!strchr(cmd_line, '$'))
		return (cmd_line);
	if(cmd_line[0] == '$' && cmd_line[1] == '?')
		return(ft_itoa(g_exit));
	//free();
	i = -1;
	new = ft_strdup("");
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '$' && cmd_line[i + 1] && (cmd_line[i + 1] == ' '
				|| cmd_line[i + 1] == '"' || cmd_line[i + 1] == '\''))
			return (cmd_line);
		if (cmd_line[i] == '$' && cmd_line[i + 1]
			&& (!is_inside_single_quotes(cmd_line, i)
				|| (is_inside_single_quotes(cmd_line, i)
					&& is_inside_quotes(cmd_line, i))))
			new = get_expanded(cmd_line, new, &i, env);
		else
		{
			c[0] = cmd_line[i];
			c[1] = '\0';
			new = ft_strjoin(new,c);
		}
	}
	//free(cmd_line);
	while(*new == 32)
	{
		if(!(**lexer->details->string == 32) && !lexer->next)
		{
			lexer->details->string++;
		}
		new++;
	}
	return (new);
}
