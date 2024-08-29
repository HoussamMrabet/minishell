/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:25:47 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 17:32:47 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	valid_identifier(char *identifier)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ft_isal(identifier[0]) && identifier[0] != '_')
		return (FALSE);
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	handle_unset(t_exec *tree, t_minishell *m, char **id)
{
	int	i[2];

	i[0] = -1;
	while (id[++i[0]])
	{
		if (valid_identifier(id[i[0]]))
		{
			if (!tree->is_pipe)
			{
				remove_env(m, id[i[0]]);
				remove_fake_env(m, id[i[0]]);
				if (!ft_strcmp(id[i[0]], "PATH"))
					m->paths = NULL;
				else if (!ft_strcmp(id[i[0]], "HOME"))
					m->home = NULL;
			}
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(id[i[0]], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(1, TRUE);
		}
	}
}

void	ft_unset(t_minishell *m, t_exec *tree)
{
	t_tokenizer	*token;
	char		**id;

	exit_status(0, TRUE);
	if (open_files_builtin(tree))
		return ;
	token = tree->tokens->next;
	while (token)
	{
		if (token->type != SPACES)
		{
			id = ft_split_local(token->token, '\002', m);
			if (!id)
			{
				ft_putstr_fd("minishell: unset: ", 2);
				ft_putstr_fd("`': not a valid identifier\n", 2);
				exit_status(1, TRUE);
			}
			else
				handle_unset(tree, m, id);
		}
		token = token->next;
	}
}
