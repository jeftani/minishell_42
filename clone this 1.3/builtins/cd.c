/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:43:30 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/09 15:17:53 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_dir(char *after, char *before, t_env *environment)
{
	t_env_elem	*element1;
	t_env_elem	*element2;

	element1 = search_env_elem(environment, "PWD");
	if (element1 == NULL)
		free(element1);
	free(element1->value);
	element1->value = ft_strdup(after);
	element2 = search_env_elem(environment, "OLDPWD");
	if (element2 == NULL)
		free(element2);
	free(element2->value);
	element2->value = ft_strdup(before);
}

int	ft_countinuous(char **cmd, t_env *enviroment)
{
	char	*value;

	value = NULL;
	if (!ft_strcmp(cmd[1], "~") || !ft_strncmp1(cmd[1], "--", 2))
	{
		value = initial_path("$HOME", enviroment->env);
		if (chdir(value) != 0)
		{
			free(value);
			return (ft_puterrfree(cmd[0], cmd[1], NULL, 1));
		}
	}
	else if (!ft_strncmp1(cmd[1], "-", ft_strlen(cmd[1])))
	{
		value = initial_path("$OLDPWD", enviroment->env);
		if (chdir(value) != 0)
		{
			free(value);
			return (ft_puterrfree(cmd[0], cmd[1], NULL, 1));
		}
	}
	else if (chdir(cmd[1]) != 0)
		continuous(value, cmd);
	return (0);
}

char	*search_env_elem1(char *key, char **env)
{
	int		location;
	int		i;
	char	*res;

	i = 0;
	if (!ft_strcmp(key, "?"))
		return ("1");
	while (env[i] && ft_strncmp1(key, env[i], ft_strlen(key)))
		i++;
	if (!env[i])
		return (NULL);
	location = ft_strchr1(env[i], '=');
	res = ft_substr(env[i], location + 1, (ft_strlen(env[i]) - location));
	return (res);
}

char	*initial_path(char *path, char **env)
{
	t_con	con;

	con.i = 0;
	con.j = 0;
	con.b = 0;
	con.d = 0;
	while (*path && path[con.i] != '$')
	{
		con.res[con.i] = path[con.i];
		con.i++;
	}
	if (path[con.i] == '$')
	{
		if (path[con.i + 1] == '?')
		{
			con.temp = con.i + 1;
			con.res[++con.i] = path[con.temp];
		}
		con.j = con.i;
	}
	ft_cont(path, &con, env);
	return (ft_strdup(con.res));
}

int	cd(t_env *environment, char **cmd)
{
	char	*res;
	char	**arr;
	char	cdp[2000];
	char	cwd[2000];

	arr = NULL;
	getcwd(cdp, sizeof(cdp));
	if (!cmd[1])
	{
		res = initial_path("$HOME", environment->env);
		if (chdir(res) != 0)
		{
			free(res);
			return (ft_puterrfree(cmd[0],
					initial_path("$HOME", environment->env),
					NULL,
					1));
		}
		free(res);
	}
	else
		ft_countinuous(cmd, environment);
	another(arr, cdp, cwd, environment);
	return (0);
}
