/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 07:14:22 by hmrabet          ###   ########.fr       */
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

static void	handle_special_cases(t_minishell *m, t_exec *tree)
{
	t_tokenizer	*t;
	t_tokenizer	*tmp;

	t = tree->tokens->next;
	while (t)
	{
		if (t->type != SPACES && t->is_expand
			&& ft_strchr(t->token, '='))
		{
			tmp = t->next;
			if (tmp && tmp->type == SPACES)
				tmp = tmp->next;
			if (tmp && tmp->chain == t->chain + 1)
			{
				t->token = ft_strjoin(t->token, " ", m, &m->local);
				t->token = ft_strjoin(t->token, tmp->token, m, &m->local);
				t->chain += 1;
				t->next = tmp->next;
				continue ;
			}
		}
		t = t->next;
	}
}

void	ft_export(t_minishell *m, t_exec *tree)
{
	t_tokenizer	*token;
	char		**cmd;

	open_files(m, tree);
	(1) && (token = tree->tokens, token = token->next);
	(token && token->type == SPACES) && (token = token->next);
	(!token) && (export_print(m->env, tree));
	handle_special_cases(m, tree);
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
