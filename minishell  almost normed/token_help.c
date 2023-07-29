/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 03:20:28 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/29 21:40:55 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_count	get_count(char **splited_arr, int i)
{
	t_count	count;

	count.r_out = 0;
	count.r_in = 0;
	count.r_app = 0;
	count.string = 0;
	count.herd = 0;
	while (splited_arr[++i] && strncmp(splited_arr[i], "|", 2) != 0)
	{
		if (strncmp(splited_arr[i], ">", 2) == 0)
			count.r_out++;
		else if (strncmp(splited_arr[i], "<", 2) == 0)
			count.r_in++;
		else if (strncmp(splited_arr[i], "<<", 3) == 0)
			count.herd++;
		else if (strncmp(splited_arr[i], ">>", 3) == 0)
			count.r_app++;
		else if ((i == 0) || (strncmp(splited_arr[i - 1], ">", 2)
				&& strncmp(splited_arr[i - 1], "<", 2)
				&& strncmp(splited_arr[i - 1], "<<", 3)
				&& strncmp(splited_arr[i - 1], ">>", 3)))
			count.string++;
	}
	count.end = i;
	return (count);
}

t_cmd	*inisia(t_cmd *details)
{
	details->string = NULL;
	details->r_in_sig = NULL;
	details->r_in_file = NULL;
	details->r_out_sig = NULL;
	details->r_out_file = NULL;
	details->r_app_sig = NULL;
	details->r_app_file = NULL;
	details->herdoc_sig = NULL;
	details->herdoc_lim = NULL;
	return (details);
}

t_cmd	*creation_a(t_cmd *details, t_count count)
{
	int	i;

	details = inisia(details);
	i = sizeof(char *);
	if (count.string)
	{
		details->string = (char **)ft_malloc((count.string + 1) * i);
		details->string[count.string] = NULL;
	}
	if (count.r_in)
	{
		details->r_in_sig = (char **)ft_malloc((count.r_in + 1) * i);
		details->r_in_file = (char **)ft_malloc((count.r_in + 1) * i);
		details->r_in_sig[count.r_in] = NULL;
		details->r_in_file[count.r_in] = NULL;
	}
	if (count.r_out)
	{
		details->r_out_sig = (char **)ft_malloc((count.r_out + 1) * i);
		details->r_out_file = (char **)ft_malloc((count.r_out + 1) * i);
		details->r_out_sig[count.r_out] = NULL;
		details->r_out_file[count.r_out] = NULL;
	}
	return (details);
}

t_cmd	*creation_b(t_cmd *details, t_count count)
{
	creation_a(details, count);
	if (count.r_app)
	{
		details->r_app_sig = (char **)ft_malloc((count.r_app + 1)
				* sizeof(char *));
		details->r_app_file = (char **)ft_malloc((count.r_app + 1)
				* sizeof(char *));
		details->r_app_sig[count.r_app] = NULL;
		details->r_app_file[count.r_app] = NULL;
	}
	if (count.herd)
	{
		details->herdoc_sig = (char **)ft_malloc((count.herd + 1)
				* sizeof(char *));
		details->herdoc_lim = (char **)ft_malloc((count.herd + 1)
				* sizeof(char *));
		details->herdoc_sig[count.herd] = NULL;
		details->herdoc_lim[count.herd] = NULL;
	}
	return (details);
}

t_index	inis_index(void)
{
	t_index	index;

	index.string = 0;
	index.r_in = 0;
	index.r_out = 0;
	index.r_app = 0;
	index.herd = 0;
	return (index);
}
