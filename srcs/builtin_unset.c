/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:09 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/14 10:21:11 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_list **env_list)
{
	int	i;
	int	ret_status;

	ret_status = 0;
	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]) || ft_strchr(argv[i], '='))
		{
			write(2, "minishell: unset: `", 19);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
			ret_status = 1;
		}
		else
		{
			if (unset_env_value(env_list, argv[i]) == -1)
				ret_status = 1;
		}
		i++;
	}
	g_exit_status = ret_status;
	return (ret_status);
}
