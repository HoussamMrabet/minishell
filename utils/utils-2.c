/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:14:24 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/23 15:33:30 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_length(int n)
{
	size_t	len;
	long	nb;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static size_t	ft_tenpow(size_t n)
{
	size_t	ten;

	ten = 1;
	if (n == 0)
		return (ten);
	while (n > 0)
	{
		ten *= 10;
		n--;
	}
	return (ten);
}

char	*ft_itoa(t_block_memory **garbage, int n)
{
	size_t	len;
	size_t	i;
	long	nb;
	char	*res;

	len = count_length(n);
	res = (char *)ft_malloc(garbage, len + 1);
	if (!res)
		return (NULL);
	nb = n;
	i = 0;
	if (nb < 0)
	{
		*res = '-';
		nb = -nb;
		i++;
		len--;
	}
	while (len-- > 0)
	{
		*(res + i++) = ((nb / ft_tenpow(len)) % 10) + 48;
	}
	*(res + i) = '\0';
	return (res);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	i = 0;
	dstlen = 0;
	while (*(dst + dstlen) && dstlen < dstsize)
	{
		dstlen++;
	}
	while (*(src + i) && dstlen + i + 1 < dstsize)
	{
		*(dst + i + dstlen) = *(src + i);
		i++;
	}
	if (dstlen + i < dstsize)
	{
		*(dst + i + dstlen) = '\0';
	}
	return (dstlen + srclen);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (srclen);
	while (*(src + i) && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (srclen);
}
