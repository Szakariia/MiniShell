/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:02:20 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/14 09:47:25 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*mypath_git(char *pwd)
{
	char			cwd[BUFF_SIZE];
	struct dirent	*sd;
	DIR				*dir;
	char			*tmp;

	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
	if (dir)
		while ((sd = readdir(dir)) != NULL)
			if (ft_strcmp(sd->d_name, ".git") == 0)
			{
				tmp = pwd;
				pwd = ft_strjoin(pwd, "\033[34;1mgit:(\033[0m\033[31;1mmaste");
				ft_memdel(&tmp);
				tmp = pwd;
				pwd = ft_strjoin(pwd, "r\033[34;1m)\033[0m \x1b[93m✗\033[0m ");
				ft_memdel(&tmp);
				closedir(dir);
				return (pwd);
			}
	closedir(dir);
	return (pwd);
}

char		*mypath(void)
{
	char		cwd[BUFF_SIZE];
	char		*pwd;
	char		*tmp;

	getcwd(cwd, sizeof(cwd));
	if (!cwd[0])
	{
		ft_putstr(" ⛔️ \x1b[31m \x1b[1m We need ");
		ft_putendl("permission to continue this programme ! \033[0m");
		exit(0);
	}
	if (ft_strcmp(cwd, "/") == 0)
		tmp = ft_strjoin("\x1b[92m➜\x1b[0;36m \x1b[1m ", "/");
	else
		tmp = ft_strjoin("\x1b[92m➜\x1b[0;36m \x1b[1m ", (ft_strrchr(cwd, 47)
					+ 1));
	pwd = ft_strjoin(tmp, " \033[0m");
	ft_memdel(&tmp);
	return (mypath_git(pwd));
}

t_list		*ft_exit(t_list *list, char **argv, char *commande)
{
	int i;

	i = 0;
	commande = NULL;
	while (argv[i])
		i++;
	if (i == 1)
	{
		free_mylist(list);
		ft_fresh(argv);
		return (NULL);
	}
	ft_putendl("exit: too many arguments");
	ft_fresh(argv);
	return (list);
}

t_list		*read_trait_commande(char *commande, t_list *list, char **argv)
{
	char	*pwd;

	pwd = mypath();
	argv = NULL;
	if ((commande = readline("$> ")) != NULL)
	{
		ft_memdel(&pwd);
		if (ft_strlen(commande) == 0)
		{
			ft_memdel(&commande);
			return (list);
		}
		add_history(commande);
		if ((list = ft_trait0(list, commande)) == NULL)
			return (NULL);
	}
	return (list);
}

int			main(int argc, char **argv, char **env)
{
	t_list		*list;
	char		*commande;

	argc = 0;
	if (!env[0])
	{
		ft_putstr(" ⛔️ \x1b[31m \x1b[1m We need The Linux ");
		ft_putendl("Environment to run this programme ! \033[0m");
		return (0);
	}
	list = stock_list(env);
	list->first = list;
	commande = ft_strnew(0);
	while (1)
	{
		if ((list = read_trait_commande(commande, list, argv)))
			continue ;
		else
			exit(0);
	}
	free_mylist(list->first);
	return (0);
}
