/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:57:26 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 06:32:11 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	valid_identifier(char *id)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	if (!id[0])
		return (FALSE);
	if (!ft_isal(id[0]) && id[0] != '_')
		return (FALSE);
	while (id[i])
	{
		if (id[i] == '+' && id[i + 1] != '=')
			return (FALSE);
		else if (id[i] == '=' || id[i] == '+')
			break ;
		i++;
	}
	while (j < i)
	{
		if (id[j] == ' ' && (id[j + 1] == '+' || id[j + 1] == '='))
			return (FALSE);
		else if (!ft_isalnum(id[j]) && id[j] != '_')
			return (FALSE);
		j++;
	}
	return (TRUE);
}

static void	assign_env(t_minishell *minishell, char *exp)
{
	int		i;
	char	*var;
	char	*val;

	i = 0;
	while (exp[i] && exp[i] != '=')
		i++;
	var = ft_malloc(minishell, &minishell->local, i + 1);
	i = 0;
	while (exp[i] && exp[i] != '=')
	{
		var[i] = exp[i];
		i++;
	}
	var[i] = '\0';
	i++;
	val = ft_strdup(exp + i, minishell, &minishell->local);
	set_fake_env_value(minishell, var, val);
	set_env_value(minishell, var, val);
	if (!ft_strcmp(var, "PATH"))
		minishell->paths = splitpaths(val, ':', minishell);
}

static void	concat_env(t_minishell *m, char *exp)
{
	int		i;
	char	*var;
	char	*val;
	char	*old_val;

	i = 0;
	while (exp[i] && exp[i] != '+')
		i++;
	var = ft_malloc(m, &m->local, i + 1);
	i = 0;
	while (exp[i] && exp[i] != '+')
	{
		var[i] = exp[i];
		i++;
	}
	(1) && (var[i] = '\0', i += 2);
	val = ft_strdup(exp + i, m, &m->local);
	old_val = get_env_value(m, var);
	if (old_val)
		val = ft_strjoin(old_val, val, m, &m->local);
	set_fake_env_value(m, var, val);
	set_env_value(m, var, val);
	if (!ft_strcmp(var, "PATH"))
		m->paths = splitpaths(ft_strjoin(get_env_value(m, "PATH"),
					val, m, &m->local), ':', m);
}

static void	handle_export2(t_minishell *minishell, char *id)
{
	int	i;

	i = 0;
	if (!ft_strchr(id, '='))
		set_env_value(minishell, id, "\002");
	else
	{
		while (id[i])
		{
			if (id[i] == '+' && id[i + 1] == '=')
			{
				concat_env(minishell, id);
				break ;
			}
			else if (id[i] == '=')
				assign_env(minishell, id);
			i++;
		}
	}
}

void	handle_export(t_exec *tree, t_minishell *m, char **id)
{
	int	i;

	i = -1;
	while (id[++i])
	{
		if (valid_identifier(id[i]))
		{
			if (!tree->is_pipe)
				handle_export2(m, id[i]);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(id[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(1, TRUE);
		}
	}
}
