/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:53:15 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 10:18:03 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*ft_trait0v2(t_list *list, char *line, char **newargv)
{
	char		**str;
	int			i;

	str = NULL;
	str = ft_strsplit(line, ';');
	i = 0;
	while (str[i])
	{
		if ((newargv = ft_filter_commande(str[i], my_magic(list))) != NULL)
		{
			if (newargv[0] && ft_strcmp(newargv[0], "exit") == 0)
			{
				ft_fresh(str);
				return (ft_exit(list, newargv, line));
			}
			list = ft_trait(newargv[0], list, newargv);
		}
		i++;
	}
	free(str);
	free(line);
	return (list);
}

t_list		*ft_trait0(t_list *list, char *line)
{
	char		**newargv;
	char		**str;

	str = NULL;
	newargv = NULL;
	if (!ft_strrchr(line, ';'))
	{
		if ((newargv = ft_filter_commande(line, my_magic(list))) != NULL)
		{
			if (newargv[0] && ft_strcmp(newargv[0], "exit") == 0)
				return (ft_exit(list, newargv, line));
			list = ft_trait(newargv[0], list, newargv);
		}
	}
	else
		return (ft_trait0v2(list, line, newargv));
	return (list);
}
