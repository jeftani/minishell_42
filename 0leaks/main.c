/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:13:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/25 04:33:27 by gloukas          ###   ########.fr       */
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
		add_history(cmd_line);
		if (!parse(cmd_line))
		{
			add_spaces(&cmd_line);
			lexer = split_pipe(cmd_line);
			lexer = get_token(&lexer, cmd_line);
			if (cmd_line)
				free(cmd_line);
			lexer = last_expand(&lexer, environment);
			lexer = delete_quoates_a(&lexer);
			ft_execute1(environment, lexer);
			free_lexer(&lexer);
			if (lexer)
				free(lexer);
		}
		else if (parse(cmd_line) == 1)
		{
			free(cmd_line);
			printf("❌\033[0;31m ERROR ❌ \033[0m\n");
		}
		else
			free(cmd_line);
	}
	printf("exit\n");
	g_exit = 0;
	exit(0);
}

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*head;
	int		i;

	head = *lexer;
	while (head)
	{
		if (head->command)
			free(head->command);
		if (head->details)
		{
			if (head->details->string)
			{
				i = -1;
				while (head->details->string[++i])
					free(head->details->string[i]);
				free(head->details->string);
			}
			if (head->details->r_in_sig)
			{
				i = -1;
				while (head->details->r_in_sig[++i])
					free(head->details->r_in_sig[i]);
				free(head->details->r_in_sig);
			}
			if (head->details->r_in_file)
			{
				i = -1;
				while (head->details->r_in_file[++i])
					free(head->details->r_in_file[i]);
				free(head->details->r_in_file);
			}
			if (head->details->r_out_sig)
			{
				i = -1;
				while (head->details->r_out_sig[++i])
					free(head->details->r_out_sig[i]);
				free(head->details->r_out_sig);
			}
			if (head->details->r_out_file)
			{
				i = -1;
				while (head->details->r_out_file[++i])
					free(head->details->r_out_file[i]);
				free(head->details->r_out_file);
			}
			if (head->details->r_app_sig)
			{
				i = -1;
				while (head->details->r_app_sig[++i])
					free(head->details->r_app_sig[i]);
				free(head->details->r_app_sig);
			}
			if (head->details->r_app_file)
			{
				i = -1;
				while (head->details->r_app_file[++i])
					free(head->details->r_app_file[i]);
				free(head->details->r_app_file);
			}
			if (head->details->herdoc_sig)
			{
				i = -1;
				while (head->details->herdoc_sig[++i])
					free(head->details->herdoc_sig[i]);
				free(head->details->herdoc_sig);
			}
			if (head->details->herdoc_lim)
			{
				i = -1;
				while (head->details->herdoc_lim[++i])
					free(head->details->herdoc_lim[i]);
				free(head->details->herdoc_lim);
			}
			free(head->details);
		}
		head = head->next;
	}
}
