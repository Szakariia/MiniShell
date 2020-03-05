/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:57:09 by szakaria          #+#    #+#             */
/*   Updated: 2019/12/08 02:21:40 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*old_pwd2(char *str, char *str2)
{
	ft_memdel(&str);
	str = ft_strjoin("OLDPWD=", str2);
	return (str);
}

t_list		*old_pwd(t_list *list)
{
	t_list		*tmp;
	char		cwd[BUFF_SIZE];
	int			len;

	len = 0;
	list->first = list;
	getcwd(cwd, sizeof(cwd));
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "PWD"
					, (len = mylen(list->first->str))) == 0)
		{
			tmp = list;
			while (tmp)
			{
				if (ft_strncmp(tmp->str, "OLDPWD", mylen(tmp->str)) == 0)
					tmp->str = old_pwd2(tmp->str, &list->first->str[len + 1]);
				tmp = tmp->next;
			}
			ft_memdel(&list->first->str);
			list->first->str = ft_strjoin("PWD=", cwd);
		}
		list->first = list->first->next;
	}
	return (list);
}

t_list		*add_pwd(t_list *list)
{
	char		**argv;
	char		cwd[BUFF_SIZE];

	argv = (char **)malloc(sizeof(char *) * 4);
	argv[3] = NULL;
	getcwd(cwd, sizeof(cwd));
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("OLDPWD");
	argv[2] = ft_strdup(cwd);
	list = my_setenv(argv, list);
	ft_memdel(&argv[1]);
	argv[1] = ft_strdup("PWD");
	list = my_setenv(argv, list);
	ft_fresh(argv);
	return (list);
}

t_list		*mini_cd2(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "OLDPWD"
					, mylen(list->first->str)) == 0)
			if (access(&list->first->str[7], F_OK) == 0)
			{
				chdir(&list->first->str[7]);
				return (list);
			}
		list->first = list->first->next;
	}
	ft_putstr("OLDPWD");
	ft_putendl(": Undefined variable.");
	return (add_pwd(list));
}
