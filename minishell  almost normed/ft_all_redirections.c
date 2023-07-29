/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:11:36 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 11:04:09 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case1(t_lexer *lexer, t_var *var)
{
	if (access(lexer->details->r_in_file[var->k], R_OK) == 0)
	{
		if (lexer->fd.in != STDIN_FILENO)
			close(lexer->fd.in);
		lexer->fd.in = open(lexer->details->r_in_file[var->k], O_RDONLY, 0666);
		if (lexer->fd.in == -1)
			error_hand("open", errno);
		var->k++;
	}
	else if (access(lexer->details->r_in_file[var->k], F_OK) == 0)
	{
		lexer->fd.in = -1;
		write(2, "Minishell:", 11);
		ft_directerror(lexer->details->r_in_file[var->k],
			" : Permission denied");
		exit(1);
	}
	else
	{
		lexer->fd.in = -1;
		write(2, "Minishell:", 11);
		ft_directerror(lexer->details->r_in_file[var->k],
			" : No such file or directory");
		exit(1);
	}
}

void	all_cases(t_lexer *lexer, t_var *var)
{
	if (lexer->command[var->x] == '"' || lexer->command[var->x] == '\'')
		var->flag = 0;
	if (lexer->command[var->x] == '>' && lexer->command[var->x + 1] == '>')
	{
		case2(lexer, var);
	}
	else if (lexer->command[var->x] == '>' && lexer->command[var->x + 1] != '>')
	{
		case3(lexer, var);
	}
	else if (lexer->command[var->x] == '<' && lexer->command[var->x + 1] != '<')
	{
		case1(lexer, var);
		var->red = 1;
	}
	else if (lexer->command[var->x] == '<' && lexer->command[var->x + 1] == '<')
	{
		case4(lexer, var);
	}
}

void	ft_redirect_outfile(t_lexer *lexer)
{
	t_var	var;

	var.red = 0;
	var.i = 0;
	var.x = 0;
	var.j = 0;
	var.k = 0;
	var.flag = 1;
	while (lexer->command[var.x])
	{
		all_cases(lexer, &var);
		var.x++;
	}
	if (var.red == 0)
		lexer->fd.out = var.fd;
}

void	ft_redirection(t_lexer *lexer)
{
	if (lexer->details->r_out_sig != NULL || lexer->details->r_app_sig != NULL
		|| lexer->details->r_in_sig != NULL
		|| lexer->details->herdoc_lim != NULL)
	{
		ft_redirect_outfile(lexer);
	}
	return ;
}
