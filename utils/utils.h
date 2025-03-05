/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:29:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/03/04 17:39:15 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

void	ft_putstr(int out, char *str);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
void    *ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
#endif
