/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:18:31 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/22 07:46:46 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	another(char **arr, char *cdp, char *cwd, t_env *environment)
{
	getcwd(cwd, sizeof(cwd));
	ft_change_dir(cwd, cdp, environment);
	arr = creat_double_array_env(environment);
	if (arr)
	{
		free(environment->env);
		environment->env = arr;
	}
	g_exit = EXIT_SUCCESS;
}

int	continuous(char *value, char **cmd)
{
	free(value);
	return (ft_puterrfree(cmd[0], cmd[1], NULL, 1));
}

void	ft_cont(char *path, t_con *con, char **env)
{
	while (path && ft_isalnum(path[++con->j]))
	{
		con->key[con->b] = path[con->j];
		con->b++;
	}
	con->key[con->b] = '\0';
	con->value = search_env_elem1(con->key, env);
	if (con->value)
	{
		while (con->value[con->d])
		{
			con->res[con->d] = con->value[con->d];
			con->d++;
		}
		con->res[++con->d] = '\0';
	}
}

char	*search_env_elem2(char *key, char **env , t_env *envi)
{
	int		location;
	int		i;
	char	*res;
	t_env_elem	*tmp;

	i = 0;
	tmp = envi->head;
	if (!ft_strcmp(key, "?"))
		return ("1");

	while (env[i] && ft_strncmp12(key, env[i], ft_strlen(tmp->key)))
	{
		i++;
		tmp = tmp->next;
	}
	//while (env[i] && ft_strncmp12(key, env[i], ft_strlen(env[i])))
		//i++;
	if (!env[i])
		return (NULL);
	location = ft_strchr1(env[i], '=');
	res = ft_substr(env[i], location + 1, (ft_strlen(env[i]) - location));
	return (res);
}
