/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 02:32:51 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/21 23:50:25 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str0;
	size_t	j;

	if (!(str0 = (char *)malloc(ft_strlen(s1) + 1)))
		return (NULL);
	j = 0;
	while (s1[j])
	{
		str0[j] = s1[j];
		j++;
	}
	str0[j] = '\0';
	return (str0);
}
