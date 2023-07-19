/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:13:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/19 01:30:41 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		j;
	t_env	*environment;

	(void)av;
	if (ac != 1)
		return (printf("❌\033[0;31m ERROR ❌ \033[0m\n"), 1);
	signal(SIGINT, interruption);
	signal(SIGQUIT, interruption);
	environment = createenvironment(env);
	environment->env = creat_double_array_env(environment);
	while (1)
	{
		i = 0;
		j = 0;
		cmd_line = readline("MINISHELL ➡ ");
		if (!cmd_line)
			break ;
		add_history(cmd_line);
		if (!parse(cmd_line))
		{
			add_spaces(&cmd_line);
			lexer = split_pipe(cmd_line);
			lexer = get_token(&lexer, cmd_line);
			lexer = delete_quoates_a(&lexer);
			cmd_line = expand(lexer->command, environment);
			lexer->command = cmd_line;
			//maybe
			//printf("===>first in string %s\n",lexer->details->string[0]);
			//printf("===>second in string %s\n",lexer->details->string[1]);
			while(lexer->details->string[i])
			{
				lexer->details->string[i] = expand(lexer->details->string[i], environment);
				i++;
			}
			ft_execute1(environment, lexer);
		}
		else if (parse(cmd_line) == 1)
			printf("❌\033[0;31m ERROR ❌ \033[0m\n");
	}
	printf("exit\n");
	g_exit = 0;
	exit(0);
}
