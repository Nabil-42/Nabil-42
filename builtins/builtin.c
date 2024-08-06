/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:54:43 by nabil             #+#    #+#             */
/*   Updated: 2024/08/06 11:56:40 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"
#include "env/env.h"

extern volatile sig_atomic_t	g_flag;

void	init_eko(t_echo *eko, t_general *g)
{
	eko->len_str = 200;
	eko->i = 0;
	eko->j = 0;
	eko->exval = g->exval;
	eko->line = NULL;
	eko->flag_i = 0;
	eko->flag = 0;
	eko->k = 0;
}

void	missingknow(t_echo *eko, t_general *g)
{
	(void)eko;
	if (g_flag == 2)
		g->exval = 130;
	if (g_flag == 3)
		g->exval = 131;
	g->flag_eko_n = 2;
}

int	execute_command(char **tab, t_echo *eko, t_env *local_env, t_general *g)
{
	(void)local_env;
	if (ft_strcmp(tab[eko->k], "echo") == 0 && ft_strcmp(tab[eko->k + 1], "$?") != 0)
		return (echo(g->petit_tab, eko, g), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[eko->k], "echo") == 0 && ft_strcmp(tab[eko->k + 1], "$?") == 0)
		return (missingknow(eko, g), free_tab(eko->tab), free_tab(g->petit_tab),
			1);
	if (ft_strcmp(tab[eko->k], "cd") == 0)
		return (cd_project(tab, g), free_tab(eko->tab), free_tab(g->petit_tab),
			1);
	if (ft_strcmp(tab[eko->k], "pwd") == 0)
		return (pwd(tab, g), free_tab(eko->tab), free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[eko->k], "env") == 0)
		return (ft_env(g), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strncmp("export",tab[eko->k], 6) == 0)
		return (ft_export(g, eko, g->petit_tab), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[eko->k], "unset") == 0)
		return (ft_unset(g, tab), free_tab(eko->tab),
			free_tab(g->petit_tab), 1);
	if (ft_strcmp(tab[eko->k], "exit") == 0)
		return (ft_exit(tab, g, eko), 1);
	return (0);
}
void skip_empty(char **tab, int *i)
{
	while (strcmp(tab[*i], "$EMPTY") == 0)
		++*i;
}

int	builtin(char *line, t_env *local_env, t_general *g)
{
	t_echo	eko;
	int		result;
	char	*test;

	eko.tab = NULL;
	test = remake_str_bis(g->tab_cmd);
	g->petit_tab = ft_split(test, ' ');
	free(test);
	eko.tab = ft_split(line, ' ');
	init_eko(&eko, g);
	if (!eko.tab[0])
		return (free_tab(g->petit_tab), free_tab(eko.tab), 0);
	skip_empty(eko.tab, &eko.k);
	if (ft_strcmp(eko.tab[eko.k], "echo") != 0 && ft_strcmp(eko.tab[eko.k], "cd") != 0
		&& ft_strcmp(eko.tab[eko.k], "pwd") != 0 && ft_strcmp(eko.tab[eko.k],
			"env") != 0 && ft_strcmp(eko.tab[eko.k], "exit") != 0
		&& eko.tab[eko.k +1] == NULL && ft_strncmp(eko.tab[eko.k], "export", 6) != 0
		&& ft_strncmp(eko.tab[eko.k], "unset", 6) != 0)
		return (free_tab(eko.tab), free_tab(g->petit_tab), 0);
	if ((ft_strcmp(eko.tab[eko.k], "echo") == 0 && eko.tab[eko.k +1] == NULL)
		|| (ft_strcmp(g->petit_tab[eko.k], "echo") == 0 && g->petit_tab[eko.k +1] == NULL))
	{
		g->flag_eko_n = 6;
		free_tab(eko.tab);
		return (free_tab(g->petit_tab), 1);
	}
	result = execute_command(eko.tab, &eko, local_env, g);
	if (result == 0)
	{
		free_tab(g->petit_tab);
		g->petit_tab = NULL;
		free_tab(eko.tab);
		eko.tab = NULL;
	}
	return (result);
}
