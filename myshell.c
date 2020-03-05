/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:00:26 by szakaria          #+#    #+#             */
/*   Updated: 2019/11/16 23:36:27 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		affichage_myenv(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		ft_putendl(list->first->str);
		list->first = list->first->next;
	}
}

t_list		*ft_myshell(char **argv, int com, t_list *list)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	if (com == 1)
		mini_echo(argv);
	else if (com == 2)
		list = mini_cd(argv, list);
	else if (com == 3)
		list = my_setenv(argv, list);
	else if (com == 4)
		list = my_unsetenv(argv, list, len);
	else if (com == 5)
		affichage_myenv(list);
	return (list);
}
