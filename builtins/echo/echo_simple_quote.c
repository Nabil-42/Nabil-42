/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_simple_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/08/12 12:07:48 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

static int	handle_consecutive_quotes_simple(char *str, t_echo *eko)
{
	if (str[eko->i] == 39 && str[eko->i + 1] == 39)
	{
		eko->line[eko->j] = '\0';
		eko->i += 2;
		return (2);
	}
	return (0);
}

static int	handle_single_double_quote_simple(char *str, t_echo *eko, int *flag)
{
	if (str[eko->i] == 39)
	{
		++(*flag);
		if (*flag == 1)
		{
			++eko->i;
		}
		else
		{
			++eko->i;
			eko->line[eko->j] = '\0';
			return (0);
		}
	}
	return (1);
}

static void	copy_non_special_char_simple(char *str, t_echo *eko, t_general *g)
{
	(void)g;
	eko->line[eko->j] = str[eko->i];
	if (str[eko->i] == '$' && str[eko->i + 1] == ' ')
	{
		++eko->j;
		eko->line[eko->j] = ' ';
	}
	++eko->i;
	++eko->j;
}

int	echo_take_of_simple_quote(char *str, t_echo *eko, int n, t_general *g)
{
	int	flag;
	int	dollar_check;
	int	result;

	flag = 0;
	result = 0;
	while (eko->i <= n)
	{
		result = handle_consecutive_quotes_simple(str, eko);
		if (result == 2)
			return (2);
		result = handle_single_double_quote_simple(str, eko, &flag);
		if (result == 0)
			return (0);
		if (flag == 0)
		{
			dollar_check = dollar_double(str, eko, g);
			if (dollar_check == -1)
				return (eko->line[eko->j] = '\0', -1);
			if (dollar_check > 0)
				continue ;
		}
		copy_non_special_char_simple(str, eko, g);
	}
	return (0);
}
