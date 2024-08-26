/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_global.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:46:42 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 18:46:44 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
		if ((s[i] != c && s[i + 1] == c)
			|| (s[i] != c && s[i + 1] == '\0'))
			count++;
	return (count);
}

static int	words_len(char *s, char c, int i)
{
	int	l;

	l = 0;
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i] && s[i++] != c)
		l++;
	return (l);
}

static char	**fill_arr(int w[], char *s, char **arr, t_minishell *m)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < w[1])
	{
		j = 0;
		arr[k] = (char *)ft_malloc(m, &m->global,
				sizeof(char) * (words_len(s, w[0], i) + 1));
		if (!arr[k])
			return (NULL);
		while (s && s[i] && s[i] == w[0])
			i++;
		while (s && s[i] && s[i] != w[0])
			arr[k][j++] = s[i++];
		arr[k][j] = '\0';
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_split_global(char *s, char c, t_minishell *m)
{
	char	**arr;
	int		words[2];

	words[0] = c;
	if (!s || !s[0])
		return (NULL);
	words[1] = word_count(s, words[0]);
	arr = (char **)ft_malloc(m, &m->global, sizeof(char *) * (words[1] + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, s, arr, m);
	return (arr);
}
