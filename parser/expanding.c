/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:27:10 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 06:29:13 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_expand_values(t_minishell *m, t_tokenizer **tokens)
{
	t_tokenizer	*tok;

	tok = *tokens;
	while (tok)
	{
		if (tok->type == TEXT)
		{
			if (tok->token && tok->token[0] == '~' && tok->token[1] == '/')
				tok->token = ft_strjoin(m->home, tok->token + 1, m, &m->local);
			else if (tok->token && tok->token[0] == '~' && !tok->token[1])
				tok->token = ft_strjoin(m->home, tok->token + 1, m, &m->local);
			handle_text_expand(m, tok, &tok->token);
		}
		else if (tok->type == D_QUOTE)
			handle_quote_expand(m, &tok->token);
		else if (tok->type == S_QUOTE)
			remove_quotes(m, &tok->token, '\'');
		tok = tok->next;
	}
}
