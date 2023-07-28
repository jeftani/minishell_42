/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:57:06 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/28 01:02:40 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_link(t_env_elem *newelem, t_env_elem *present)
{
	if (ft_strchr(newelem->key, '+') && present->value)
	{
		present->value = ft_strjoin(present->value, newelem->value);
		free(newelem->value);
	}
	else if (ft_strchr(newelem->key, '=') && present->value)
	{
		present->value = ft_strjoin(present->value, newelem->value);
		free(newelem->value);
	}
	else
	{
		present->value = newelem->value;
		//free(present->value);
	}
}

int	ft_strncmp12(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && n > i && s1[i]
		&& s2[i])
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_resume(t_env *environment)
{
	char	**arr;

	arr = NULL;
	arr = creat_double_array_env(environment);
	if (arr)
	{
		free(environment->env);
		environment->env = arr;
	}
}

void	ft_maintain(char **cmd, int i, int j, t_env *environment)
{
	while (cmd[j])
	{
		while (cmd[1][i] && (ft_isalnum(cmd[1][i]) || (cmd[1][i] == '+'
					&& cmd[1][i + 1] == '=')))
			i++;
		if (i < ft_strchr2(cmd[1], '='))
		{
			if (environment->l != 10)
				ft_puterr(cmd[0], cmd[j], "not a valid identifier",
					EXIT_FAILURE);
			break ;
			//test here cuz when it break will return exit status 0 which is success.
		}
		else if ((cmd[1][i] == '=' || cmd[j]) && environment->l == 0)
			add_var(environment, cmd[j]);
		j++;
	}
}
