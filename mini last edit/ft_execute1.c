/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:01:12 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/22 05:36:28 by ajeftani         ###   ########.fr       */
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

char	**retreive_path(t_env *environment, t_lexer *lexer)
{
	char	**path;
	char	*path_line;
	int		i;

	i = 0;
	if(find_it(environment, "PATH") == NULL)
		{
			return (ft_err(&lexer->command[0], "No such file or directory", 0),exit(127), NULL);
		}
	while (environment->env[i])
	{
		while (ft_strnstr(environment->env[i], "PATH", 4) == NULL)
		{
			i++;
			if (environment->env[i] == NULL)
				break ;
		}
		break ;
	}
	path_line = ft_strnstr(environment->env[i], "PATH", 4);
	if (path_line)
	{
		path = ft_split((path_line + 5), ':');
		if (!path)
			error_hand("Split function failed", 1);
		return (path);
	}
	return (forward(lexer));
	return (NULL);
}

void	execute_command(t_env *environment, t_lexer *lexer)
{
	char	**splited;
	char	*cmd;
	int		num;

	signal(SIGINT, interruption);
	signal(SIGQUIT, interruption);
	splited = retreive_path(environment, lexer);

	while(lexer->command[0] == '\0')
	{
		return;
	}
	cmd = get_cmd(splited, lexer);
	if (!cmd)
	{
		//free_paths(splited);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(ft_strtrim(&lexer->command[0], "\""), 2);
		ft_putstr_fd(": Command not found\n", 2);
		exit(127);
	}
	num = execve(cmd, lexer->details->string, environment->env);
	if (num == -1)
		error_execv(lexer, splited);
}

void	execute_child(t_lexer *lexer, t_env *environment, int *fd)
{
	signal(SIGINT, interruption);
	signal(SIGQUIT, interruption);
	close(fd[0]);
	ft_redirection(lexer);
	dup_close(&lexer->fd);
	close(fd[1]);
	if (check_builtings(lexer->details->string))
	{
		ft_execute(environment, lexer->details->string);
	}
	else
		execute_command(environment, lexer);
	exit(0);
}

void	executing(t_env *environment, t_lexer *lexer)
{
	int		fd[2];
	pid_t	pid;

	if (lexer->details->string)
	{
		while (lexer && lexer->next)
		{
			if (pipe(fd) == -1)
				error_hand("pipe", errno);
			pipe(fd);
			redirect_the_std(lexer);
			check_it(lexer, fd);
			pid = fork();
			if (pid == -1)
				error_hand("fork", errno);
			if (pid == 0)
				execute_child(lexer, environment, fd);
			else
				parent(lexer, fd);
			lexer = lexer->next;
		}
		if (lexer && lexer->command != NULL)
			ft_execute_one(environment, lexer);
		waitchilds();
	}
	// free1.
	free(lexer->details);
}

void	ft_execute1(t_env *environment, t_lexer *lexer)
{
	if (!run_heredoc(lexer, environment))
		// means if it return 0 which is success it will convert to 1 and enter that shit. sus here commentaire with if it is ignored.
		executing(environment, lexer);
	else
		g_exit = 1;
}
