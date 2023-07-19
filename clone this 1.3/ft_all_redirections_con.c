/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_redirections_con.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:22:06 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/13 20:56:05 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case4(t_lexer *lexer, t_var *var)
{
	// added and works how and why nobody knows.
	close(lexer->fd.in);
	lexer->fd.in = open("/tmp/minishell", O_RDWR, 0644);
	var->x++;
	var->red = 1;
}

void	case3(t_lexer *lexer, t_var *var)
{
	var->fd = open(lexer->details->r_out_file[var->j],
			O_CREAT | O_RDWR | O_TRUNC,
			0644);
	if (var->fd == -1)
	{
		error_hand("open", errno);
		//break ; // be careful
	}
	var->j++;
	var->red = 0;
}

void	case2(t_lexer *lexer, t_var *var)
{
	var->fd = open(lexer->details->r_app_file[var->i],
			O_CREAT | O_RDWR | O_APPEND,
			0644);
	var->x++;
	var->i++;
	var->red = 0;
}
