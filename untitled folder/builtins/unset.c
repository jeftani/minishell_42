/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 00:28:46 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 10:31:35 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	proceed(t_env *environment)
{
	char	**arr;

	arr = creat_double_array_env(environment);
	if (arr)
	{
		free(environment->env);
		environment->env = arr;
	}
}

void	remove_from_list(t_env *environment, t_env_elem *temp)
{
	if (temp)
	{
		if (temp == environment->head)
			environment->head = temp->next;
		if (temp->prev)
			temp->prev->next = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
	}
	free(temp->key);
	free(temp->value);
	free(temp);
	environment->size--;
}

void	unset(t_env *environment, char **cmd)
{
	int			i;
	t_env_elem	*temp;

	i = 1;
	if (!cmd[i])
		return ;
	if (!(ft_is_alpha(cmd[1][0])))
	{
		printf("minishell: unset: '%s': not a valid identifier\n", cmd[1]);
		g_exit = EXIT_FAILURE;
	}
	if (!cmd[i])
		return ;
	while (cmd[i])
	{
		temp = NULL;
		temp = search_env_elem(environment, cmd[i]);
		if (temp)
			remove_from_list(environment, temp);
		proceed(environment);
		i++;
	}
	g_exit = EXIT_SUCCESS;
}
