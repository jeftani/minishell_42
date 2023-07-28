/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:12:35 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/27 23:18:42 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_elem	*search_env_elem(t_env *env, char *key)
{
	t_env_elem	*tmp;
	int			len;

	tmp = env->head;
	len = ft_strlen(key);
	if (ft_strchr1(key, '+'))
		len--;
	while (tmp && ft_strncmp12(tmp->key, key, len))
	{
		tmp = tmp->next;
	}
	while (tmp && ft_strncmp12(tmp->key, key, ft_strlen(tmp->key)))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	add_var(t_env *environment, char *line)
{
	t_env_elem	*newelem;
	t_env_elem	*present;
	char		**arr;

	arr = NULL;
	newelem = new_element(line);
	present = search_env_elem(environment, newelem->key);
	if (present)
	{
		ft_link(newelem, present);
		free(newelem->key);
		free(newelem);
	}
	else
		add_env_elem(environment, newelem);
	ft_resume(environment);
}

void	print_env_sorted(t_env_elem *content)
{
	while (content)
	{
		if (content->key)
			printf("declare -x %s", content->key);
		if (content->value && content->equal)
		{
			if (content->value[0] != '\"')
				printf("=\"%s\"", content->value);
			else
				printf("=%s", content->value);
		}
		else if (content->equal && content->value)
			printf("=\"\"");
		printf("\n");
		content = content->next;
	}
}

void	print_env(t_env *environment)
{
	char		*sentence1;
	char		*sentence2;
	char		*sentence3;
	t_env_elem	*content;

	content = environment->head;
	while (content->next)
	{
		if (ft_strcmp(content->key, content->next->key) > 0)
		{
			sentence1 = content->key;
			sentence2 = content->next->key;
			sentence3 = content->value;
			content->key = sentence2;
			content->next->key = sentence1;
			content->value = content->next->value;
			content->next->value = sentence3;
			content = environment->head;
		}
		else
			content = content->next;
	}
	content = environment->head;
	print_env_sorted(content);
}

int	export(t_env *environment, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	environment->l = 0;
	j = 1;
	if (!cmd[1])
	{
		if (environment->head)
			print_env(environment);
		else
			return (0);
	}
	else
	{
		if (!ft_is_alpha(cmd[1][i]))
		{
			ft_puterr(cmd[0], cmd[j], "not a valid identifier", EXIT_FAILURE);
			environment->l = 10;
		}
		i++;
		ft_maintain(cmd, i, j, environment);
	}
	g_exit = EXIT_SUCCESS;
	return (g_exit);
}
