/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_filter2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:34:28 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 09:32:58 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_2eme(int len, char *cont, int index)
{
	len++;
	while (cont[len])
	{
		if (cont[len] == index)
			return (len);
		len++;
	}
	return (0);
}

char		*ft_myjoin(char *newline, char c)
{
	int		i;
	char	*tmp;

	tmp = ft_strnew(ft_strlen(newline) + 1);
	i = -1;
	while (newline[++i])
		tmp[i] = newline[i];
	tmp[i] = c;
	tmp[i + 1] = '\0';
	ft_memdel(&newline);
	return (tmp);
}

t_my		*env_variable_return(t_my *my)
{
	if (my->tmp4[0])
		ft_memdel(&my->tmp4);
	if (my->new)
		ft_memdel(&my->new);
	free(my);
	return (NULL);
}

t_my		*env_variablev2(char *cont, char **env, int per22, t_my *my)
{
	t_my	*my2;

	my2 = NULL;
	per22 = 0;
	if ((cont[my->i] != '~' || my->per != 0) && cont[my->i] != '$')
		my->new = ft_myjoin(my->new, my->c);
	if ((my->per2 != 2 || my->per == 0) && cont[my->i] == '~')
	{
		if ((my2 = home_user(cont, my, env)) != NULL)
			my = my2;
		else
			return (env_variable_return(my));
	}
	if (cont[my->i] == '$')
	{
		if ((my2 = dollar_and_home(cont, my, env)) != NULL)
			my = my2;
		else
			return (env_variable_return(my));
	}
	return (my);
}

char		*env_variable(char *cont, char **env, int per22, int x)
{
	char	*resul;
	t_my	*my;
	t_my	*my2;

	my = malloc(sizeof(t_my));
	my = initialisation_variablev2(my);
	my->tmp4 = my->new;
	my->x = x;
	while (cont[my->i])
	{
		my->c = cont[my->i];
		if ((my2 = env_variablev2(cont, env, per22, my)) != NULL)
			my = my2;
		else
			return (return_env_variable(my));
		my->i++;
	}
	resul = my->new;
	if (&my->tmp4[0] == '\0')
		ft_memdel(&my->tmp4);
	free(my);
	return (resul);
}
