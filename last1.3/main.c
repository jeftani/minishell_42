/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:13:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/14 13:32:44 by ajeftani         ###   ########.fr       */
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

int	main(int ac, char **av , char **env)
{
	char	*cmd_line;
	t_lexer	*lexer;
	int		i;
	int		j;

	(void)av;
	if (ac != 1)
	{
		printf("❌\033[0;31m ERROR ❌ \033[0m\n");
		return (1);
	}
	signal(SIGINT, interruption);
	signal(SIGQUIT, interruption);
    t_env *environment;
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
			cmd_line = expand(cmd_line,environment);
			lexer = split_pipe(cmd_line);
			lexer = get_token(&lexer, cmd_line);
			lexer = delete_quoates_a(&lexer);
			t_lexer *temp;
			temp = lexer;
			//print elements
			//while (lexer != NULL)
			//{
			//	printf("Command: %s\n", lexer->command);
			//	if (lexer->details != NULL)
			//	{
			//		if (lexer->details->string)
			//			printf("String: %s\n", *(lexer->details->string));
			//		if (lexer->details->r_out_sig)
			//			printf("Output Signal: %s\n",
			//					*(lexer->details->r_out_sig));
			//		if (lexer->details->r_in_sig)
			//			printf("Input Signal: %s\n",
			//					*(lexer->details->r_in_sig));
			//		if (lexer->details->r_in_file)
			//			printf("Input File: %s\n",
			//					*(lexer->details->r_in_file));
			//		if (lexer->details->r_out_file)
			//			printf("Output File: %s\n",*(lexer->details->r_out_file));
			//		if (lexer->details->r_app_sig)
			//			printf("Append Signal: %s\n",
			//					*(lexer->details->r_app_sig));
			//		if (lexer->details->r_app_file)
			//			printf("Append File: %s\n",
			//					*(lexer->details->r_app_file));
			//		if (lexer->details->herdoc_sig)
			//			printf("Heredoc Signal: %s\n",
			//					*(lexer->details->herdoc_sig));
			//		if (lexer->details->herdoc_lim)
			//			printf("Heredoc Limit: %s\n",
			//					*(lexer->details->herdoc_lim));
			//	}
			//	printf("**********\n");
			//	lexer = lexer->next;
			//}
			ft_execute1(environment,temp);
			//end
		}
		else
			printf("❌\033[0;31m ERROR ❌ \033[0m\n");
		free(lexer);
		free(cmd_line);

	}
	printf("exit\n");
	g_exit = 0;
	exit(0);
}
