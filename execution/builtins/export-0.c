/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 16:35:50 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_print(char	**env, t_exec *tree)
{
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", tree->fdout);
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], tree->fdout);
		if (env[i][j] && env[i][j] == '=')
		{
			ft_putstr_fd("=\"", tree->fdout);
			if (env[i][++j])
				ft_putstr_fd(env[i] + j, tree->fdout);
			ft_putstr_fd("\"", tree->fdout);
		}
		ft_putstr_fd("\n", tree->fdout);
		i++;
	}
	return (0);
}

void	ft_export(t_minishell *m, t_exec *tree)
{
	t_tokenizer	*token;
	char		**cmd;

	open_files(m, tree);
	(1) && (token = tree->tokens, token = token->next);
	(token && token->type == SPACES) && (token = token->next);
	(!token) && (export_print(m->env, tree));
	while (token)
	{
		if (token->type != SPACES)
		{
			cmd = ft_split_local(token->token, '\002', m);
			if (!cmd && token->type != TEXT)
			{
				ft_putstr_fd("minishell: export: ", 2);
				ft_putstr_fd("`': not a valid identifier\n", 2);
				exit_status(1, TRUE);
			}
			else
				handle_export(tree, m, cmd);
		}
		token = token->next;
	}
}
