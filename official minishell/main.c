/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:13:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/28 16:03:48 by ajeftani         ###   ########.fr       */
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
	//this is a test
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
		if(ft_strncmp(cmd_line,"\0",1))
			add_history(cmd_line);
		if(cmd_line == '\0')
			free(cmd_line);
		if (!parse(cmd_line))
		{
			add_spaces(&cmd_line);
			lexer = split_pipe(cmd_line);
			lexer = get_token(&lexer, cmd_line);
			t_lexer *temp;
			temp = lexer;

			while (lexer != NULL)
			{
				if(lexer && lexer->command)
				{
					lexer->command = expand(lexer->command, environment,lexer);
				}
				while(lexer && lexer->details && lexer->details->string && lexer->details->string[i])
				{
									lexer->details->string[i] = expand(lexer->details->string[i], environment,lexer);
									i++;
				}
				i = 0;
				while(lexer && lexer->details && lexer->details->string && lexer->details->string[i] && lexer->details->string[i][0] == '$')
				{
						lexer->details->string[i] = expand(lexer->details->string[i], environment,lexer);
							i++;
				}
				lexer = lexer->next;
			}
			temp = delete_quoates_a(&temp);
			ft_execute1(environment, temp);
		}
		else if (parse(cmd_line) == 1)
			printf("❌\033[0;31m ERROR ❌ \033[0m\n");
	}
	printf("exit\n");
	g_exit = 0;
	exit(0);
}
