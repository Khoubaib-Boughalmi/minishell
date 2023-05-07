/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:34:53 by khoubaib          #+#    #+#             */
/*   Updated: 2023/05/07 10:25:03 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_return_index(const char *ptr, unsigned long *i)
{
	short					sign;

	sign = 1;
	while ((*(ptr + *i) >= 9 && *(ptr + *i) <= 13) || *(ptr + *i) == 32)
		*i += 1;
	if (*(ptr + *i) == '+' || *(ptr + *i) == '-')
	{
		if (*(ptr + *i) == '-' )
			sign = -1;
		*i += 1;
	}
	return (sign);
}

long long	ft_atoi(const char *ptr)
{
	unsigned long	i;
	long long		res;
	short			sign;

	res = 0;
	i = 0;
	sign = ft_return_index(ptr, &i);
	while ((ptr[i] >= '0' && ptr[i] <= '9') && ptr[i] != '\0')
	{
		res = res * 10;
		res += ptr[i] - '0';
		i++;
	}
	return (res * sign);
}
