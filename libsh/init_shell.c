/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/02 12:30:25 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_sh     *init_shell(void)
{
    t_sh *new;

    if (!(new = malloc(sizeof(t_sh))))
        ms_malloc_error();
    new->cmd = NULL;
    if (!(new->env = ms_get_env()))
        new->env = NULL;
    return (new);
}