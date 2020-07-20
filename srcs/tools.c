/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:29:39 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/13 17:39:37 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char    *file_name(char *str)
{
    int     i;
    int     j;
    int     k;
    char    *file_name;
    
    i = 0;
    j = 0;
    while (str[i])
        i++;
    i -= 2;
    k = i;
    while (k != 0 && str[k] != '/')
        k--;
    if (k != 0)
        k++;
    k = 0;
    file_name = malloc(sizeof(char) * ((i - k) + 1));
    i = i - k;
    while (j < i)
        file_name[j++] = str[k++];
    return(file_name);
}
