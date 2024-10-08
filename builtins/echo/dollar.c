/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:06:47 by nabil             #+#    #+#             */
/*   Updated: 2024/08/11 22:38:31 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

char	*extract_env_variable_name(char *str, int *i)
{
	char	*variable_env;
	int		k;

	variable_env = malloc(PATH_MAX + 1);
	k = 0;
	if (variable_env == NULL)
		return (NULL);
	++(*i);
	if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		while (str[*i])
		{
			if (ft_isalnum(str[*i]) || str[*i] == '_')
			{
				variable_env[k] = str[*i];
				++*i;
				k++;
			}
			else
				break ;
		}
	}
	variable_env[k] = '\0';
	return (variable_env);
}

int	handle_variable_expansion(char *str, t_echo *eko, int *i, t_general *g)
{
	char	*variable_env;
	char	*name;
	int		k;

	(void)g;
	variable_env = extract_env_variable_name(str, i);
	if (variable_env == NULL)
		return (0);
	name = ft_getenv(&g->local_env, variable_env);
	free(variable_env);
	if (name == NULL)
	{
		return (0);
	}
	k = 0;
	while (name[k])
	{
		eko->line[eko->j++] = name[k++];
	}
	free(name);
	return (1);
}

void	copy_normal_char_bis(char *str, t_echo *eko, int *i, t_general *g)
{
	(void)g;
	(eko->line[eko->j++] = str[*i]);
	++(*i);
}

void	copy_normal_char(char *str, t_echo *eko, int *i, t_general *g)
{
	char	*itoua;
	int		k;

	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		k = 0;
		itoua = ft_itoa(g->exval);
		while (itoua[k])
		{
			eko->line[eko->j] = itoua[k];
			++eko->j;
			k++;
		}
		++*i;
	}
	else
		(eko->line[eko->j++] = str[*i]);
	++(*i);
}

int	dollar(char *str, t_echo *eko, t_general *g)
{
	int	i;

	i = 0;
	eko->j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?'
			&& str[i + 1] != ' ')
		{
			if (!handle_variable_expansion(str, eko, &i, g))
			{
				if (str[i] != '\0')
					++i;
			}
			continue ;
		}
		copy_normal_char(str, eko, &i, g);
	}
	eko->line[eko->j] = '\0';
	return (0);
}
