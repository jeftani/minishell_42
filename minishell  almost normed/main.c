/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:13:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/29 15:14:26 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run(char *cmd_line, t_lexer *lexer, t_env *environment, int i)
{
	t_lexer	*temp;

	add_spaces(&cmd_line);
	lexer = split_pipe(cmd_line);
	lexer = get_token(&lexer, cmd_line);
	temp = lexer;
	while (lexer != NULL)
	{
		ft_boucle(lexer, i, environment);
		lexer = lexer->next;
	}
	temp = delete_quoates_a(&temp);
	ft_execute1(environment, temp);
}

void	ft_continue(int i, t_lexer *lexer, t_env *environment, char *cmd_line)
{
	while (1)
	{
		i = 0;
		cmd_line = readline("MINISHELL ➡ ");
		if (!cmd_line)
			break ;
		check_cmd(cmd_line);
		if (!parse(cmd_line))
		{
			ft_run(cmd_line, lexer, environment, i);
		}
		else if (parse(cmd_line) == 1)
			ft_else(cmd_line);
		else
			free(cmd_line);
	}
}

void	interruption(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	char	*cmd_line;
	t_lexer	*lexer;
	int		i;
	t_env	*environment;

	cmd_line = NULL;
	lexer = NULL;
	i = 0;
	(void)av;
	if (ac != 1)
		return (printf("❌\033[0;31m ERROR ❌ \033[0m\n"), 1);
	signal(SIGINT, interruption);
	signal(SIGQUIT, interruption);
	environment = createenvironment(env);
	environment->env = creat_double_array_env(environment);
	ft_continue(i, lexer, environment, cmd_line);
	printf("exit\n");
	g_exit = 0;
	exit(0);
}
