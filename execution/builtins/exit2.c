/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:26:29 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/26 18:34:25 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(long long res, char *str, int i, int sign)
{
	int	n;

	while (str[i] <= '9' && str[i] >= '0')
	{
		n = (str[i] - '0') * sign;
		if (res > LLONG_MAX / 10
			|| (res == (LLONG_MAX / 10) && n > 7))
			return (0);
		if (res < LLONG_MIN / 10
			|| (res == (LLONG_MIN / 10) && n < -8))
			return (0);
		res = res * 10 + n;
		i++;
	}
	return (1);
}

int	overfllow_checker(char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = check_overflow(res, str, i, sign);
	return (res);
}
