/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:29:25 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 11:51:37 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_mylist(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		ft_memdel(&tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = tmp->next;
	}
}

void		ft_print(char **str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putstr(str[i++]);
}

void		ok_x_pathv2(char **argv, t_list *list, DIR *dir, char **env)
{
	int pid;

	pid = 0;
	if (access(argv[0], X_OK) == 0 && (dir = opendir(argv[0])) == NULL)
	{
		env = my_magic(list);
		if ((pid = fork()) > 0)
			wait(0);
		if (pid == 0)
			execve(argv[0], argv, env);
		free(env);
	}
	else
	{
		if (dir != NULL)
			closedir(dir);
		ft_putstr("minishell : permission denied:");
		ft_putendl(argv[0]);
	}
}

void		ok_x_path(char **argv, t_list *list)
{
	struct stat	sb;
	char		**env;
	DIR			*dir;

	env = NULL;
	dir = NULL;
	if (argv[0] && lstat(argv[0], &sb) > -1)
		ok_x_pathv2(argv, list, dir, env);
	else
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(argv[0]);
	}
}

t_list		*ft_trait(char *commande, t_list *list, char **argv)
{
	if (!commande)
		return (return_vide(list, argv));
	if (!ft_strcmp(commande, "echo"))
		list = ft_myshell(argv, 1, list);
	else if (!ft_strcmp(commande, "cd"))
		list = ft_myshell(argv, 2, list);
	else if (!ft_strcmp(commande, "setenv"))
		list = ft_myshell(argv, 3, list);
	else if (!ft_strcmp(commande, "unsetenv"))
		list = ft_myshell(argv, 4, list);
	else if (!ft_strcmp(commande, "env"))
		list = ft_myshell(argv, 5, list);
	else if (commande[0] && search_commande(list, commande, argv) == 0)
	{
		if (ft_strchr(argv[0], '/'))
			ok_x_path(argv, list);
		else
		{
			ft_putstr("minishell: command not found: ");
			ft_putstr(commande);
			ft_putchar('\n');
		}
	}
	ft_fresh(argv);
	return (list);
}
