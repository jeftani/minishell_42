/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:11:02 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/22 05:26:41 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**forward(t_lexer *lexer)
{
	if (access(&lexer->command[0], F_OK) == 0)
		return (NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(&lexer->command[0], 2);
	ft_putstr_fd(": No such file or directory ", 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

void	ft_err(char *str, char *message, int c)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 11);
	if (c == 1)
		write(2, "cd: ", 4);
	if (c == 2)
		write(2, "export: ", 8);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, ": ", 2);
	i = 0;
	while (message[i])
		write(2, &message[i++], 1);
	write (1, "\n", 1);
}
