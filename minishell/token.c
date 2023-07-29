/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:34:54 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/29 01:22:41 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_empty_element(char *cmd_line)
{
	int		len;
	char	**new_arr;
	char	**splited_arr;
	int		i;
	int		j;

	len = 0;
	splited_arr = arg_split(cmd_line);
	while (splited_arr[len])
		len++;
	new_arr = (char **)ft_malloc((len + 1) * sizeof(char *));
	i = -1;
	while (++i <= len)
		new_arr[i] = NULL;
	j = 0;
	i = -1;
	while (++i < len)
	{
		if (splited_arr[i][0] != '\0')
		{
			new_arr[j] = splited_arr[i];
			j++;
		}
	}
	return (new_arr);
}

t_lexer	*get_token(t_lexer **lexer, char *cmd_line)
{
	char	**splited_arr;
	t_count	count;
	int		i;
	t_index	index;
	t_lexer	*head;

	i = 0;
	head = *lexer;
	splited_arr = remove_empty_element(cmd_line);
	if (!ft_strncmp(splited_arr[0], ">", 2) && splited_arr[1])
		case7(head->vas, splited_arr[1]);
	while (splited_arr[i])
	{
		count = get_count(splited_arr, i - 1);
		head->details = ft_malloc(sizeof(t_cmd));
		head->details = creation_b(head->details, count);
		index = inis_index();
		while (splited_arr[i] && i != count.end)
		{
			head = function_help_a(head, &index, splited_arr, &i);
			i++;
		}
		if (splited_arr[i])
			i++;
		head = head->next;
	}
	return (*lexer);
}

t_lexer	*function_help_a(t_lexer *head, t_index *index, char **splited_arr,
		int *i)
{
	int	check;

	check = (*i);
	if (!ft_strncmp(splited_arr[(*i)], "<", 2))
	{
		head->details->r_in_sig[index->r_in] = ft_substr(splited_arr[(*i)++], 0,
				2);
		head->details->r_in_file[index->r_in++] = ft_substr(splited_arr[(*i)],
															0,
															ft_strlen(splited_arr[(*i)]));
	}
	else if (!ft_strncmp(splited_arr[(*i)], ">", 2))
	{
		head->details->r_out_sig[index->r_out] = ft_substr(splited_arr[(*i)++],
															0,
															2);
		head->details->r_out_file[index->r_out++] = ft_substr(splited_arr[(*i)],
																0,
																ft_strlen(splited_arr[(*i)]));
	}
	if (check == (*i))
		head = function_help_b(head, index, splited_arr, i);
	return (head);
}

t_lexer	*function_help_b(t_lexer *head, t_index *index, char **splited_arr,
		int *i)
{
	if (!ft_strncmp(splited_arr[(*i)], ">>", 3))
	{
		head->details->r_app_sig[index->r_app] = ft_substr(splited_arr[(*i)++],
															0,
															3);
		head->details->r_app_file[index->r_app++] = ft_substr(splited_arr[(*i)],
																0,
																ft_strlen(splited_arr[(*i)]));
	}
	else if (!ft_strncmp(splited_arr[(*i)], "<<", 3))
	{
		head->details->herdoc_sig[index->herd] = ft_substr(splited_arr[(*i)++],
															0,
															3);
		head->details->herdoc_lim[index->herd++] = ft_substr(splited_arr[(*i)],
																0,
																ft_strlen(splited_arr[(*i)]));
	}
	else
	{
		head->details->string[index->string++] = ft_substr(splited_arr[(*i)], 0,
				ft_strlen(splited_arr[(*i)]));
	}
	return (head);
}
