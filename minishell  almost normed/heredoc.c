/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:18:00 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 11:09:46 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_hand(void)
{
	exit(1);
}

void	to_do_her(char *delimiter, t_env *env)
{
	char	*str;
	int		fd;

	fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("minishell");
		return ;
	}
	str = readline("> ");
	while (str && ft_strcmp(str, delimiter))
	{
		str = expand(str, env, NULL);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}

int	open_heredoc(t_lexer *lexer, t_env *env)
{
	int		i;
	char	*delimiter;
	pid_t	j;

	i = 0;
	while (lexer->details->herdoc_lim[i])
	{
		delimiter = lexer->details->herdoc_lim[i];
		j = fork();
		if (j == 0)
		{
			to_do_her(delimiter, env);
			exit(0);
		}
		else
		{
			waitpid(j, &g_exit, 0);
			if (g_exit)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	run_heredoc(t_lexer *lexer, t_env *environment)
{
	int	count;
	int	i;

	count = 0;
	if (lexer->details->herdoc_lim == NULL)
	{
		return (0);
	}
	while (lexer->details->herdoc_sig[count])
		count++;
	i = open_heredoc(lexer, environment);
	return (i);
}
