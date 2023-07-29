/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_extra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:53:08 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 15:15:14 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char *cmd_line)
{
	if (ft_strncmp(cmd_line, "\0", 1))
		add_history(cmd_line);
	if (cmd_line == '\0')
		free(cmd_line);
}

void	ft_else(char *cmd_line)
{
	free(cmd_line);
	printf("❌\033[0;31m ERROR ❌ \033[0m\n");
}

void	ft_boucle(t_lexer *lexer, int i, t_env *environment)
{
	if (lexer && lexer->command)
		lexer->command = expand(lexer->command, environment, lexer);
	while (lexer && lexer->details && lexer->details->string
		&& lexer->details->string[i])
	{
		lexer->details->string[i] = expand(
				lexer->details->string[i],
				environment,
				lexer);
		i++;
	}
	i = 0;
	while (lexer && lexer->details && lexer->details->string
		&& lexer->details->string[i] && lexer->details->string[i][0] == '$')
	{
		lexer->details->string[i] = expand(
				lexer->details->string[i],
				environment,
				lexer);
		i++;
	}
}
