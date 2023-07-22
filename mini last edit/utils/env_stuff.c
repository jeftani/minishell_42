/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:38:07 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/22 04:27:42 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_double_array_env(t_env *environment)
{
	t_env_elem	*temp;
	char		**arr;
	int			j;

	temp = environment->head;
	arr = malloc((environment->size + 1) * sizeof(char *));
	//printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, arr);
	if (!arr)
	{
		return (NULL);
	}
	j = 0;
	while (temp)
	{
		arr[j] = ft_strdup(temp->key);
		if (temp->value)
		{
			arr[j] = ft_strjoin(arr[j], "=");
			arr[j] = ft_strjoin(arr[j], temp->value);
		}
		temp = temp->next;
		j++;
		arr[j] = NULL;
	}
	return (arr);
}

void	add_env_elem(t_env *env, t_env_elem *new)
{
	t_env_elem	*tmp;

	tmp = env->head;
	if (!env->head)
	{
		env->head = new;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
	}
	env->size++;
}

t_env_elem	*new_element(char *line)
{
	t_env_elem	*env_element;
	char		*key;
	char		*value;
	int			index;

	//int equal;
	index = 0;
	index = ft_strchr1(line, '=');
	env_element = malloc(sizeof(t_env_elem));
	//printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, env_element);
	env_element->next = NULL;
	env_element->prev = NULL;
	if (index != 0)
	{
		key = ft_substr(line, 0, index);
		value = ft_substr(line, index + 1, ft_strlen1(line));
		env_element->key = key;
		env_element->value = value;
		env_element->equal = 1;
	}
	else
	{
		env_element->key = ft_strdup(line);
		env_element->value = NULL;
	}
	return (env_element);
}

t_env	*inisialize(t_env *environment)
{
	environment = malloc(sizeof(t_env));
	//printf(": ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, environment);
	if (!environment)
		return (NULL);
	environment->head = NULL;
	environment->size = 0;
	return (environment);
}

t_env	*createenvironment(char **env)
{
	int		i;
	t_env	*environment;

	i = 0;
	environment = NULL;
	environment = inisialize(environment);
	environment->env = env;
	while (env[i])
	{
		add_env_elem(environment, new_element(env[i++]));
	}
	return (environment);
}
