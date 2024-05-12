/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 12:23:29 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *var)
{
	int	i;

	i = 0;
	if (!var[i] || (!ft_isal(var[i]) && var[i] != '_'))
		return (1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if ((var[i] != '_' && var[i] != '+' && !ft_isalnum(var[i]))
			|| (var[i] == '+' && var[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}

static int	export_print(char	**env)
{
	int		i;
	int		j;
	t_bool	bool;

	(1) && (i = 0, j = 0, bool = FALSE);
	while (env[i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j])
		{
			printf("%c", env[i][j]);
			if (env[i][j] == '=')
				printf("\"");
			(env[i][j] == '=') && (bool = !bool);
			if (bool && !env[i][j + 1])
				printf("\"");
			(bool && !env[i][j + 1]) && (bool = !bool);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

static int	handle_export(t_minishell *minishell, char *splited)
{
	int	i;

	i = 0;
	if (!ft_strchr(splited, '='))
		set_env_value(minishell, splited, "\002");
	else
	{
		while (splited[i])
		{
			if (splited[i] == '+' && splited[i + 1] == '=')
			{
				concat_env(minishell, splited);
				break ;
			}
			else if (splited[i] == '=')
				assign_env(minishell, splited);
			i++;
		}
	}
	return (0);
}

void	ft_export(t_minishell *m, char *cmd)
{
	char	**splited;
	int		i[2];
	char	*sub;

	(1) && (i[1] = 0, i[0] = -1);
	while (cmd[++i[0]])
		if (cmd[i[0]] == '\n' && (cmd[i[0] + 1] == '\n' || !cmd[i[0] + 1]))
			(1) && (sub = ft_substr(&m->local, cmd, 0, i[0]),
				sub = ft_strjoin(sub, "\n\002", &m->local),
				cmd = ft_strjoin(sub, cmd + i[0] + 1, &m->local));
	(1) && (splited = ft_split(cmd, '\n', &m->local), i[0] = 1);
	(!splited[i[0]]) && export_print(m->env);
	if (splited[i[0]])
	{
		while (splited[i[0]])
		{
			(splited[i[0]][0] == 2) && (splited[i[0]][0] = '\0');
			(!check_syntax(splited[i[0]])) && (handle_export(m, splited[i[0]]));
			(check_syntax(splited[i[0]])) && (i[1]
				= printf("minishell: export: `%s': not a valid identifier\n",
					splited[i[0]]), i[1] = 1);
			i[0]++;
		}
	}
	exit_status(i[1], TRUE);
}
