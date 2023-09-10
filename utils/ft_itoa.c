/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:39:35 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/06 05:58:32 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long int	ft_absoluteint(long n)
{
	if (n < 0)
		n = n * -1;
	return (n);
}

static void	ft_fillres(long long_n, char *res, int len_res)
{
	while (long_n >= 10)
	{
		res[len_res] = long_n % 10 + 48;
		long_n /= 10;
		len_res--;
	}
	res[len_res] = long_n + 48;
}

char	*ft_itoa(int n)
{
	long	long_n;
	char	*res;
	int		len_res;

	len_res = 0;
	long_n = ft_absoluteint((long)n);
	while (long_n >= 10)
	{
		len_res++;
		long_n /= 10;
	}
	len_res++;
	if (n < 0)
		len_res++;
	long_n = ft_absoluteint(n);
	res = ft_calloc(len_res + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	ft_fillres(long_n, res, len_res - 1);
	return (res);
}
