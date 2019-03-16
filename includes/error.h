/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:22:13 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:38:28 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

#include "../libft/libft.h"
#include "../libsh/libsh.h"

ssize_t		too_many_args(char *cmd);
void		error_option(char c);
int			syntax_error(char *str);
ssize_t		unvalid_setenv_cmd(void);
ssize_t		error_chdir(int error, char *path, char *cmd);
int			ambiguous_redirect(char *arg);

#endif