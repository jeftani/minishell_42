/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:08:41 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/28 23:19:12 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	putstr_trim(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(1, &cmd[i], 1);
		i++;
	}
}

void	output_echo(char **cmd, int i)
{
	 putstr_trim(cmd[i]);
	if (cmd[i + 1])
		write(1, " ", 1);
}

int	echo(char **cmd,t_lexer *lexer)
{
	int	flag;
	int	i;
	int j;

	flag = 0;
	i = 0;
	j = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
	}
	while (cmd[i + 1] && cmd[i + 1][j] == '-' && cmd[i + 1][j + 1] == 'n')
	{
		j = 0;
		while(cmd[i + 1][j + 1] == 'n')
			j++;
		if(cmd[i + 1][j + 1] == '\0')
		{
			flag = 1;
			++i;
			j = 0;
		}
		else
			break;
	}
	while (cmd[++i])
	{
		output_echo(cmd, i);
		if (!cmd[i + 1] && !flag && j == 0)
			write(1, "\n", 1);
	}
	if (lexer->details->r_out_file)
	    {
	        close(1);
	        dup2(lexer->original_stdout, 1);
	        close(lexer->original_stdout);
	    }
	g_exit = EXIT_SUCCESS;
	return (g_exit);
}
