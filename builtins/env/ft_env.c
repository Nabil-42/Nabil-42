/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/07/30 19:14:07 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

static char	*tvar_to_str(t_var *var);

void	ft_env(t_general *g)
{
	char	**local_env;
	int		i;

	g->flag_eko_n = 3;
	local_env = get_local_env(&g->local_env);
	i = 0;
	while (local_env[i])
	{
		if (local_env[i])
			printf("%s\n", local_env[i]);
		i++;
	}
	delete_envp(local_env);
	free(local_env);
}

char	*ft_getenv(t_env *env, char *key)
{
	t_list	*lst_iter;
	t_var	*var;
	int		hash;

	hash = hash_function(key, MAX_ENV);
	lst_iter = env->env_p[hash];
	while (lst_iter)
	{
		var = (t_var *)(lst_iter->content);
		if (ft_strcmp(key, var->key) == 0)
		{
			return (var->value);
		}
		lst_iter = lst_iter->next;
	}
	return (NULL);
}

char	**get_local_env(t_env *env)
{
	t_list	*lst_iter;
	t_var	*var;
	char	**local_env;
	int		i;
	int		j;

	local_env = malloc(sizeof(void *) * (env->nb_var + 1));
	if (!local_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < MAX_ENV)
	{
		lst_iter = env->env_p[i];
		while (lst_iter)
		{
			var = (t_var *)(lst_iter->content);
			if (var->env_flag)
				local_env[j++] = tvar_to_str(var);
			lst_iter = lst_iter->next;
		}
		i++;
	}
	local_env[j] = NULL;
	return (local_env);
}

static char	*tvar_to_str(t_var *var)
{
	char *str;
	char *tmp;

	tmp = ft_strjoin(var->key, "=");
	str = ft_strjoin(tmp, var->value);
	free(tmp);
	return (str);
}