/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:40:55 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/13 14:23:35 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = ft_memalloc(len + 1);
	// cpy = (char *)malloc((len + 1) * (sizeof(char)));
	if (cpy == NULL)
		return (NULL);
	while (i < (len + 1) && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
