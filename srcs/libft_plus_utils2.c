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

static int	parse_sign_and_skip(const char **str)
{
	int	sign;
	int	signcnt;

	sign = 1;
	signcnt = 0;
	while (ft_isspace(**str))
		(*str)++;
	while (**str == 43 || **str == 45)
	{
		if (**str == '-')
			sign *= -1;
		signcnt++;
		(*str)++;
	}
	if (signcnt > 1)
	{
		errno = EINVAL;
		return (0);
	}
	return (sign);
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

static long long	parse_and_check_digits(const char **str, int sign)
{
	long long	res;
	int			digit;

	res = 0;
	while (ft_isdigit(**str))
	{
		digit = **str - '0';
		if (is_overflow(res, digit, sign))
		{
			errno = ERANGE;
			return (handle_overflow(sign));
		}
		res = res * 10 + digit;
		(*str)++;
	}
	return (res);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	errno = 0;
	sign = parse_sign_and_skip(&str);
	if (errno == EINVAL)
		return (0);
	if (!ft_isdigit(*str))
	{
		errno = EINVAL;
		return (0);
	}
	res = parse_and_check_digits(&str, sign);
	if (*str != '\0')
	{
		errno = EINVAL;
		return (0);
	}
	return (res * sign);
}
