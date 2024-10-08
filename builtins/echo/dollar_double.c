/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/08/12 12:04:57 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

#define PATH_MAX 4096

char	*extract_variable_name(char *str, t_echo *eko)
{
	char	*variable_env;
	int		k;

	variable_env = malloc(PATH_MAX + 1);
	k = 0;
	if (variable_env == NULL)
		return (NULL);
	while (((str[eko->i] >= 'A' && str[eko->i] <= 'Z') || (str[eko->i] >= 'a'
				&& str[eko->i] <= 'z')) && str[eko->i] != '\0')
	{
		variable_env[k] = str[eko->i];
		++k;
		++eko->i;
	}
	variable_env[k] = '\0';
	return (variable_env);
}

int	expand_variable(char *variable_env, t_echo *eko, t_general *g)
{
	char	*name;
	int		k;

	name = ft_getenv(&g->local_env, variable_env);
	if (name == NULL)
		return (-1);
	k = 0;
	while (name[k])
	{
		eko->line[eko->j] = name[k];
		++eko->j;
		++k;
	}
	free(name);
	return (1);
}

int	dollar_double(char *str, t_echo *eko, t_general *g)
{
	char	*variable_env;
	int		result;

	if (str[eko->i] != '$')
		return (0);
	if (str[eko->i] == '$' && str[eko->i + 1] == ' ')
		return (0);
	if (str[eko->i] == '$' && str[eko->i + 1] == '\0')
		return (0);
	if (str[eko->i] == '$' && str[eko->i + 1] == '"')
		return (0);
	if (str[eko->i] == '$' && str[eko->i + 1] == '?')
		return (0);
	++eko->i;
	variable_env = extract_variable_name(str, eko);
	if (variable_env == NULL)
		return (0);
	result = expand_variable(variable_env, eko, g);
	free(variable_env);
	return (result);
}

int	dollar_bis(char *str, t_echo *eko, t_general *g)
{
	int	i;

	i = 0;
	eko->j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] != '\0' && str[i + 1] != '?'))
		{
			if (!handle_variable_expansion(str, eko, &i, g))
				return (0);
			continue ;
		}
		copy_normal_char_bis(str, eko, &i, g);
	}
	eko->line[eko->j] = '\0';
	return (0);
}
