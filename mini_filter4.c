/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_filter4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:31:39 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 11:48:37 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*filter_return(t_my *my)
{
	if (my->tmp4[0])
		ft_memdel(&my->tmp4);
	if (my->new[0])
		ft_memdel(&my->new);
	free(my);
	return (NULL);
}

int			serach_env(char *cont, char **env, int per)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], &cont[1], mylen2(env[i], &cont[1])) == 0)
			return (i);
		i++;
	}
	if (per == 0)
	{
		ft_putstr(&cont[1]);
		ft_putstr(": Undefined variable.\n");
	}
	return (-1);
}

int			ft_search126(char *cont)
{
	int	i;

	i = 0;
	while (cont[i])
	{
		if (cont[i] == '~')
			return (i);
		i++;
	}
	return (-1);
}

t_my		*dollar_and_home2(char *cont, t_my *my, char **env)
{
	my->x = -1;
	my->per++;
	my->start = my->i;
	my->i++;
	while (cont[my->i] && cont[my->i] != 34 && cont[my->i] != 39
			&& ft_isalnum(cont[my->i]))
		my->i++;
	my->i--;
	my->tmp = ft_strsub(cont, my->start, (my->i - my->start + 1));
	my->x = serach_env(my->tmp, env, 0);
	if (my->per2 != 0 && my->x > -1)
	{
		my->tmp2 = my->new;
		my->new = ft_strjoin(my->new, (&env[my->x][ft_strlen(my->tmp)]));
		ft_memdel(&my->tmp2);
	}
	else if (my->x > -1)
		my->new = ft_strjoin(my->new, my->tmp);
	ft_memdel(&my->tmp);
	return (my);
}

t_my		*dollar_and_home(char *cont, t_my *my, char **env)
{
	if (cont[my->i] == '$' && (cont[my->i + 1] == '~'
				|| cont[my->i + 1] == '/'))
	{
		ft_memdel(&my->new);
		ft_putendl("Illegal variable name.");
		return (NULL);
	}
	else if (cont[my->i] == '$' && cont[my->i + 1] == '$')
	{
		my->tmp = my->new;
		my->tmp3 = ft_itoa(getppid());
		my->new = ft_strjoin(my->new, my->tmp3);
		ft_memdel(&my->tmp3);
		ft_memdel(&my->tmp);
		my->i++;
	}
	else if (cont[my->i] == '$' && cont[my->i + 1] == '\0')
	{
		my->tmp = my->new;
		my->new = ft_strjoin(my->new, "$");
		ft_memdel(&my->tmp);
	}
	else if (cont[my->i] == '$')
		my = dollar_and_home2(cont, my, env);
	return (my);
}
