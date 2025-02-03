/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:44:43 by macampos          #+#    #+#             */
/*   Updated: 2025/01/17 18:34:09 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_data	*get(void)
{
	static t_data	data;

	return(&data);
}

int main(int argc, char **argv)
{
    if (argc != 2 || open(argv[1], O_RDONLY) == -1)
    {
        ft_putstr_fd("wrong input", 2);
        return(1);
    }
    parsing(argv[1], open(argv[1], O_RDONLY));
    mlx_start();
	return(0);
}
