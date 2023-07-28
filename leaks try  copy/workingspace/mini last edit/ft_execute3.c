/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:19:11 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/27 23:18:42 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close(t_fd *fd)
{
	if (fd->in != STDIN_FILENO && fd->in > 0)
	{
		dup2(fd->in, STDIN_FILENO);
	}
	if (fd->out != STDOUT_FILENO && fd->out > 1)
	{
		dup2(fd->out, STDOUT_FILENO);
	}
}

void	ft_execute_one(t_env *environment, t_lexer *lexer)
{
	pid_t	pid;

	if (dir(&lexer->command[0]))
		return ;
	if (check_builtings(lexer->details->string))
	{
		ft_execute(environment, lexer->details->string);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			ft_redirection(lexer);
			check_filed(lexer);
			execute_command(environment, lexer);
		}
		else
		{
			close_it(lexer);
			waitpid(pid, &g_exit, 0);
		}
	}
}

void	waitchilds(void)
{
	signal(SIGINT, interruption);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
		g_exit = WTERMSIG(g_exit);
}

void	parent(t_lexer *lexer, int fd[])
{
	close(fd[1]);
	if (lexer->fd.in != STDIN_FILENO)
		close(lexer->fd.in);
	if (lexer->fd.out != STDOUT_FILENO)
		close(lexer->fd.out);
	lexer = lexer->next;
	g_exit = 999;
}

char	*get_cmd(char **splited, t_lexer *lexer)
{
	int		i;
	char	*temp;
	char	*res;

	i = 0;
	if (!splited)
	{
		return (ft_strdup(lexer->command));
	}
	if (ft_strchrr(lexer->command, '/'))
	{
		while(lexer->command[i] && lexer->command[i] != ' ')
			i++;
		lexer->command[i] = '\0';
		return (lexer->command);
	}
	i = 0;
	while (splited[i])
	{
		temp = ft_strjoin(splited[i], "/");
		res = ft_strjoin(temp, lexer->details->string[0]); //[0]
		//free(temp);
		if (access(res, F_OK) == 0)
		{
			return (res);
		}
		//free(splited);
		i++;
	}
	return (NULL);
}
