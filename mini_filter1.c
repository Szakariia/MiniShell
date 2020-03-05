/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_filter1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:26:23 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 09:37:58 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_my		*filter_string2v2v2(t_my *my)
{
	if (my->i - my->j + 1 > 0)
		ft_memdel(&my->tmp2);
	my->tmp2 = my->new;
	my->new = ft_strjoin(my->new, my->tmp);
	ft_memdel(&my->tmp2);
	ft_memdel(&my->tmp);
	return (my);
}

t_my		*filter_string2v2(char *argv, char **env, t_my *my)
{
	if (my->per != 0 && argv[my->i] == '~')
	{
		my->tmp = my->new;
		my->new = ft_strjoin(my->new, "~");
		ft_memdel(&my->tmp);
		my->i++;
	}
	my->j = my->i;
	while (argv[my->i] && argv[my->i] != 34 && argv[my->i] != 39)
		my->i++;
	my->i--;
	my->tmp2 = ft_strsub(argv, my->j, my->i - my->j + 1);
	if ((my->tmp = env_variable(my->tmp2, env, 2, 0)) != NULL)
		my = filter_string2v2v2(my);
	else
	{
		ft_memdel(&my->tmp2);
		return (NULL);
	}
	return (my);
}

t_my		*filter_string1v2(char *argv, char **env, t_my *my)
{
	my->per++;
	if (argv[my->i] == 39)
		my->per2 = 0;
	if (my->i + 1 < ft_2eme(my->i, argv, ((int)argv[my->i])))
	{
		my->tmp2 = ft_strsub(argv, my->i + 1,
				ft_2eme(my->i, argv, ((int)argv[my->i])) - my->i - 1);
		if ((my->tmp = env_variable(my->tmp2, env, my->per2, 1)) != NULL)
		{
			if (ft_2eme(my->i, argv, ((int)argv[my->i])) - my->i - 1 > 0)
				ft_memdel(&my->tmp2);
			my->tmp2 = my->new;
			my->new = ft_strjoin(my->new, my->tmp);
			ft_memdel(&my->tmp2);
			ft_memdel(&my->tmp);
		}
		else
		{
			ft_memdel(&my->tmp2);
			return (NULL);
		}
	}
	my->i = ft_2eme(my->i, argv, ((int)argv[my->i]));
	return (my);
}

char		*filter_string3(char *argv, char **env, char *new, t_my *my)
{
	t_my	*my2;

	my2 = NULL;
	if (argv[my->i] == 34 || argv[my->i] == 39)
	{
		if ((my2 = filter_string1v2(argv, env, my)) != NULL)
			new = my2->new;
		else
			return (filter_return(my));
	}
	else if (argv[my->i] != 34 && argv[my->i] != 39)
	{
		if ((my2 = filter_string2v2(argv, env, my)) != NULL)
			new = my2->new;
		else
			return (filter_return(my));
	}
	return (new);
}

char		*filter_string2(char *argv, char **env, char *new)
{
	t_my		*my;
	char		*tmp;

	my = malloc(sizeof(t_my));
	my = initialisation_variablev2(my);
	my->tmp4 = my->new;
	tmp = NULL;
	while (argv[my->i])
	{
		if ((tmp = filter_string3(argv, env, new, my)) != NULL)
			new = tmp;
		else
			return (NULL);
		my->i++;
	}
	free(my);
	return (new);
}
