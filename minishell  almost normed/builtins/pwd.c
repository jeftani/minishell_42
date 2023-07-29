/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:05 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/14 12:20:17 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	cmd[256];
	char	*res;

	res = getcwd(cmd, sizeof(cmd));
	if (!res)
	{
		perror("minishell: pwd: ");
		g_exit = EXIT_FAILURE;
	}
	printf("%s\n", cmd);
	g_exit = EXIT_SUCCESS;
}
