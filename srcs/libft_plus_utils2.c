/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:08:28 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 16:08:31 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	parse_sign_and_skip(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
	{
		(*str)++;
		return (1);
	}
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	return (1);
}

static int	is_overflow(long long res, int digit, int sign)
{
	if (sign == 1)
	{
		if (res > LLONG_MAX / 10)
			return (1);
		if (res == LLONG_MAX / 10 && digit > LLONG_MAX % 10)
			return (1);
		return (0);
	}
	else
	{
		if (res < LLONG_MIN / 10)
			return (1);
		if (res == LLONG_MIN / 10 && digit > -(LLONG_MIN % 10))
			return (1);
		return (0);
	}
}

static long long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;
	int			digit;

	res = 0;
	sign = parse_sign_and_skip(&str);
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (is_overflow(res, digit, sign))
		{
			errno = ERANGE;
			return (handle_overflow(sign));
		}
		res = res * 10 + digit;
		str++;
	}
	if (*str != '\0')
	{
		errno = EINVAL;
		return (0);
	}
	return (res * sign);
}
