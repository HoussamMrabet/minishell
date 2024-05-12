/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:57:26 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 20:43:11 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_env(t_minishell *minishell, char *exp)
{
	int		i;
	char	*var;
	char	*val;

	i = 0;
	while (exp[i] && exp[i] != '=')
		i++;
	var = ft_malloc(&minishell->local, i + 1);
	i = 0;
	while (exp[i] && exp[i] != '=')
	{
		var[i] = exp[i];
		i++;
	}
	var[i] = '\0';
	i++;
	val = ft_strdup(exp + i, &minishell->local);
	set_fake_env_value(minishell, var, val);
	set_env_value(minishell, var, val);
	if (!ft_strcmp(var, "PATH"))
		minishell->paths = ft_split(val, ':', &minishell->global);
}

void	concat_env(t_minishell *minishell, char *exp)
{
	int		i;
	char	*var;
	char	*val;
	char	*old_val;

	i = 0;
	while (exp[i] && exp[i] != '+')
		i++;
	var = ft_malloc(&minishell->local, i + 1);
	i = 0;
	while (exp[i] && exp[i] != '+')
	{
		var[i] = exp[i];
		i++;
	}
	var[i] = '\0';
	i += 2;
	val = ft_strdup(exp + i, &minishell->local);
	old_val = get_env_value(minishell, var);
	if (old_val)
		val = ft_strjoin(old_val, val, &minishell->local);
	set_fake_env_value(minishell, var, val);
	set_env_value(minishell, var, val);
	if (!ft_strcmp(var, "PATH"))
		minishell->paths = ft_split(val, ':', &minishell->global);
}
