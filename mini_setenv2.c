/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:56:12 by szakaria          #+#    #+#             */
/*   Updated: 2019/11/18 14:56:14 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			trait_my_setenv2(char *argv, int i)
{
	while (argv[i])
	{
		if (!ft_isalnum(((int)argv[i])))
			return (0);
		i++;
	}
	return (1);
}

int			tarit_my_setnvv2(char **argv, int j)
{
	while (argv[j])
	{
		if (j == 1)
			if (argv[1][0] != '_' && (ft_isalpha(((int)argv[1][0])) == 0
						|| trait_my_setenv2(argv[j], 1) == 0))
			{
				ft_putstr("setenv: ");
				ft_putendl("Variable name must begin with a letter.");
				return (0);
			}
		j++;
	}
	return (1);
}

int			tarit_my_setnv(char **argv, t_list *list)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i])
		i++;
	j = 1;
	if (i == 3 || i == 2)
	{
		if (tarit_my_setnvv2(argv, j) == 0)
			return (0);
	}
	else
	{
		if (i == 1)
			affichage_myenv(list);
		else
			ft_putendl("setenv: Too many arguments.");
		return (0);
	}
	return (1);
}
