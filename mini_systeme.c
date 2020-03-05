/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_systeme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:04:03 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 10:12:41 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_fresh(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_memdel(&tab[i++]);
	free(tab);
	tab = NULL;
}

char		*serach_env2(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "PATH", mylen(list->first->str)) == 0)
			return (&list->first->str[5]);
		list->first = list->first->next;
	}
	return (NULL);
}

char		*join_path(char *path1, char *path2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path1, "/");
	tmp2 = ft_strjoin(tmp, path2);
	ft_memdel(&tmp);
	return (tmp2);
}

int			ft_joinandsearch(char *path, char *commande, char **argv, t_list *l)
{
	struct stat sb;
	char		*newpath;
	char		**env;
	int			pid;

	if (commande[0] == '/')
		return (0);
	newpath = join_path(path, commande);
	if (lstat(newpath, &sb) > -1)
	{
		signal(SIGINT, proc_signal_handler);
		if ((pid = fork()) > 0)
			wait(0);
		if (pid == 0)
		{
			env = my_magic(l);
			execve(newpath, argv, env);
			free(env);
		}
		ft_memdel(&newpath);
		return (1);
	}
	ft_memdel(&newpath);
	return (0);
}

int			search_commande(t_list *list, char *commande, char **argv)
{
	char	**path;
	int		len;

	path = NULL;
	len = 0;
	if (serach_env2(list))
	{
		path = ft_strsplit(serach_env2(list), ':');
		len = 0;
		while (path[len])
			if (ft_joinandsearch(path[len++], commande, argv, list) == 1)
			{
				ft_fresh(path);
				return (1);
			}
		if (path[0])
			ft_fresh(path);
	}
	return (0);
}
