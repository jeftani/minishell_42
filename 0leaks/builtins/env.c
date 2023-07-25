/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:35:47 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/23 15:09:33 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_env(t_env *environment, char **cmd)
{
	int			i;
	t_env_elem	*elem;

	elem = environment->head;
	i = 0;
	if (!cmd[1])
	{
		while (i < environment->size)
		{
			if ((ft_strchr1(environment->env[i], '=') != 0) || elem->equal == 1)
				printf("%s\n", environment->env[i]);
			i++;
			elem = elem->next;
		}
		g_exit = EXIT_SUCCESS;
	}
	else
	{
		g_exit = EXIT_FAILURE;
		ft_putstr_fd("Minishell: env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
}
