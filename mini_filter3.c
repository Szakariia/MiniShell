/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_filter3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:30:35 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 11:25:47 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_my		*initialisation_variable(t_my *my, int per22)
{
	my->new = ft_strnew(0);
	my->tmp = NULL;
	my->tmp2 = NULL;
	my->tmp3 = NULL;
	my->per2 = per22;
	my->x = 0;
	my->start = 0;
	my->per = 0;
	my->i = 0;
	return (my);
}

t_my		*home_user3(char *s, t_my *my, char **env)
{
	my->i++;
	my->start = my->i;
	while (s[my->i])
		my->i++;
	my->i--;
	my->tmp = ft_strsub(s, my->start, (my->i - my->start + 1));
	if (serach_env("$HOME", env, 0) > -1)
		my->tmp2 = ft_strdup(&env[serach_env("$HOME", env, 0)][5]);
	my->x = ft_strlen(my->tmp2) - ft_strlen(ft_strrchr(my->tmp2, '/') + 1);
	my->tmp3 = ft_strsub(my->tmp2, 0, my->x);
	ft_memdel(&my->tmp2);
	my->new = ft_strjoin(my->tmp3, my->tmp);
	ft_memdel(&my->tmp3);
	if (access(my->new, F_OK) != 0)
	{
		ft_putstr("minishell: no such user or named directory:");
		ft_putendl(my->tmp);
		if (my->i - my->start + 1 > 0)
			ft_memdel(&my->tmp);
		return (NULL);
	}
	ft_memdel(&my->tmp);
	return (my);
}

t_my		*home_user2(char *s, t_my *my, char **env)
{
	t_my	*my2;

	my2 = NULL;
	if (ft_isalnum(s[my->i + 1]) && my->i == 0)
	{
		if ((my2 = home_user3(s, my, env)) != NULL)
			my = my2;
		else
		{
			return (NULL);
		}
	}
	else if (serach_env("$HOME", env, 0) > -1)
	{
		my->tmp = my->new;
		my->new = ft_strjoin(my->new, (&env[serach_env("$HOME", env, 0)][5]));
		ft_memdel(&my->tmp);
	}
	return (my);
}

t_my		*home_user(char *cont, t_my *my, char **env)
{
	t_my	*my2;

	my2 = NULL;
	if (my->i >= 1 && cont[my->i - 1] == '/')
		my->x = 1;
	if (cont[my->i] == '~' && (cont[my->i + 1] == '~' || my->x == 1))
	{
		while (cont[my->i] == '~')
		{
			my->tmp = my->new;
			my->new = ft_strjoin(my->new, "~");
			ft_memdel(&my->tmp);
			my->i++;
		}
		my->i--;
	}
	else if ((my2 = home_user2(cont, my, env)) != NULL)
		my = my2;
	else
		return (NULL);
	return (my);
}
