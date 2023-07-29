/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:45:27 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/23 15:48:46 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_it(t_env *environment, char *key)
{
	while (environment->head)
	{
		if (ft_strcmp(key, environment->head->key) == 0)
			return (environment);
		environment->head = environment->head->next;
	}
	return (NULL);
}

char	**ft_handl(t_lexer *lexer, t_env *environment)
{
	if (find_it(environment, "PATH") == NULL)
	{
		return (ft_err(&lexer->command[0], "No such file or directory", 0),
			exit(127),
			NULL);
	}
	return (environment->env);
}
