/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:57:44 by szakaria          #+#    #+#             */
/*   Updated: 2019/11/18 13:18:43 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_putstr2(char *s1, char *s2)
{
	ft_putstr(s1);
	ft_putendl(s2);
	return (0);
}

char		*serach_home(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "HOME", mylen(list->first->str)) == 0)
			return (&list->first->str[5]);
		list->first = list->first->next;
	}
	return (NULL);
}

int			test_dir(char *argv)
{
	DIR	*dir;

	if (ft_strcmp(argv, "-") && access(argv, F_OK) == -1)
	{
		ft_putstr2(argv, ": No such file or directory.");
		return (0);
	}
	else if ((dir = opendir(argv)) == NULL)
	{
		ft_putstr2("cd: not a directory: ", argv);
		return (0);
	}
	else if (dir)
		closedir(dir);
	return (1);
}

t_list		*mini_cd(char **argv, t_list *list)
{
	int			i;

	i = 1;
	while (argv[i])
		i++;
	i--;
	if (argv[1] && !argv[1][0])
		return (list);
	if (i > 1)
		ft_putendl("cd: Too many arguments.");
	if (i == 1 && ft_strcmp(argv[1], "-") == 0)
		list = mini_cd2(list);
	else if (i == 1 && test_dir(argv[1]) == 0)
		return (list);
	else
	{
		if ((i == 0 || ft_strcmp(argv[1], "~") == 0)
				&& access(serach_home(list), F_OK) == 0)
			chdir(serach_home(list));
		if (access(argv[1], F_OK) == 0)
			chdir(argv[1]);
	}
	list = old_pwd(list);
	return (list);
}
