/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_redirections_con.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:22:06 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/28 15:56:55 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	case7(t_var *var,char *name)
{
	(void)var;
	int fd = open(name,O_CREAT | O_RDWR | O_TRUNC,0644);
	if (fd == -1)
	{
		error_hand("open", errno);
	}
}

void	case4(t_lexer *lexer, t_var *var)
{
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
