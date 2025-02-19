/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:12:48 by macampos          #+#    #+#             */
/*   Updated: 2025/02/19 15:31:29 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	findx(t_image *image, int side)
{
	float	z;
	int		x;

	z = 0.0;
	if (get()->step_x > 0 && (side == 2 || side == 3))
		z = get()->realpx + get()->ray_dx * get()->distance;
	else if (get()->step_x < 0 && (side == 2 || side == 3))
		z = get()->realpx - fabs(get()->ray_dx * get()->distance);
	else if (get()->step_y < 0 && (side == 1 || side == 0))
		z = get()->realpy - get()->ray_dy * get()->distance;
	else if (get()->step_y > 0 && (side == 1 || side == 0))
		z = get()->realpy + fabs(get()->ray_dy * get()->distance);
	z = z - (int)z;
	x = z * image->width;
	return (x);
}

int	findy(t_image *image, int height, int y)
{
	float	z;
	int		x;

	z = (float)image->height / height;
	if (get()->distance < 1)
		y += ((WINDOW_HEIGHT / get()->distance - WINDOW_HEIGHT) / 2);
	x = (int)(y * z);
	return (x);
}

void	draw_vertical_line(int x, int height, int side)
{
	int	start;
	int	end;
	int	y;

	y = 0;
	start = (WINDOW_HEIGHT / 2) - (height / 2);
	end = start + height;
	while (y < start)
	{
		my_pixel_put(&get()->images[3], x, y, create_trgb(get()->texture->c[0],
				get()->texture->c[1], get()->texture->c[2]));
		y++;
	}
	y = start;
	while (y < end && y < WINDOW_HEIGHT)
	{
		if (side == 0)
		{
			my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[5],
					findx(get()->images[0], side), findy(get()->images[0],
						WINDOW_HEIGHT / get()->distance, y - start), 0));
		}
		else if (side == 1)
		{
			my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[4],
					findx(get()->images[0], side), findy(get()->images[0],
						WINDOW_HEIGHT / get()->distance, y - start), 0));
		}
		else if (side == 2)
		{
			my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[0],
					findx(get()->images[0], side), findy(get()->images[0],
						WINDOW_HEIGHT / get()->distance, y - start), 0));
		}
		else if (side == 3)
		{
			my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[1],
					findx(get()->images[5], side), findy(get()->images[0],
						WINDOW_HEIGHT / get()->distance, y - start), 0));
		}
		y++;
	}
	y = end;
	while (y < WINDOW_HEIGHT)
	{
		my_pixel_put(&get()->images[3], x, y, create_trgb(get()->texture->f[0],
				get()->texture->f[1], get()->texture->f[2]));
		y++;
	}
}

float	cast_single_ray(void)
{
	float	dist_x;
	float	dist_y;

	get()->calcx = get()->realpx;
	get()->calcy = get()->realpy;
	get()->ray_dx = cos((get()->ray_angle + 0.001) * (3.1415926 / 180));
	get()->ray_dy = sin((get()->ray_angle + 0.001) * (3.1415926 / 180));
	if (get()->ray_dx < 0)
		get()->step_x = -1;
	else
		get()->step_x = 1;
	if (get()->ray_dy < 0)
		get()->step_y = 1;
	else
		get()->step_y = -1;
	if (get()->step_x > 0)
		get()->side_distx = ((int)(get()->calcx + 1) - get()->calcx);
	else
		get()->side_distx = (get()->calcx - (int)get()->calcx);
	if (get()->step_y > 0)
		get()->side_disty = ((int)(get()->calcy + 1) - get()->calcy);
	else
		get()->side_disty = (get()->calcy - (int)get()->calcy);
	dist_x = get()->side_distx / fabs(get()->ray_dx);
	dist_y = get()->side_disty / fabs(get()->ray_dy);
	while (1)
	{
		if (dist_x < dist_y)
		{
			get()->calcx += get()->step_x;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				return (fabs(dist_x));
			}
			dist_x += fabs(1 / get()->ray_dx);
		}
		else
		{
			get()->calcy += get()->step_y;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				return (fabs(dist_y));
			}
			dist_y += fabs(1 / get()->ray_dy);
		}
	}
}

int	check_side(void)
{
	float	dist_x;
	float	dist_y;

	get()->calcx = get()->realpx;
	get()->calcy = get()->realpy;
	get()->ray_dx = cos((get()->ray_angle + 0.001) * (3.1415926 / 180));
	get()->ray_dy = sin((get()->ray_angle + 0.001) * (3.1415926 / 180));
	if (get()->ray_dx < 0)
		get()->step_x = -1;
	else
		get()->step_x = 1;
	if (get()->ray_dy < 0)
		get()->step_y = 1;
	else
		get()->step_y = -1;
	if (get()->step_x > 0)
		get()->side_distx = ((int)(get()->calcx + 1) - get()->calcx);
	else
		get()->side_distx = (get()->calcx - (int)get()->calcx);
	if (get()->step_y > 0)
		get()->side_disty = ((int)(get()->calcy + 1) - get()->calcy);
	else
		get()->side_disty = (get()->calcy - (int)get()->calcy);
	dist_x = get()->side_distx / fabs(get()->ray_dx);
	dist_y = get()->side_disty / fabs(get()->ray_dy);
	while (1)
	{
		if (dist_x < dist_y)
		{
			get()->calcx += get()->step_x;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				if (get()->ray_dx > 0)
					return (0);
				else
					return (1);
			}
			dist_x += fabs(1 / get()->ray_dx);
		}
		else
		{
			get()->calcy += get()->step_y;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				if (get()->ray_dy > 0)
					return (2);
				else
					return (3);
			}
			dist_y += fabs(1 / get()->ray_dy);
		}
	}
}

void	raycasting(void)
{
	get()->angle_increment = get()->fov / WINDOW_LENGTH;
	get()->x = 0;
	while (get()->x < WINDOW_LENGTH)
	{
		get()->ray_angle = get()->player_angle + (get()->fov / 2) - (get()->x
			* get()->angle_increment);
		if (get()->ray_angle < 0)
			get()->ray_angle += 360.0f;
		if (get()->ray_angle > 360.0f)
			get()->ray_angle -= 360.0f;
		get()->distance = cast_single_ray();
		if (get()->distance < 0.01f)
			get()->distance = 0.1f;
		get()->wallheight = (int)(WINDOW_HEIGHT / get()->distance);
		if (get()->wallheight > WINDOW_HEIGHT)
			get()->wallheight = WINDOW_HEIGHT;
		draw_vertical_line(get()->x, get()->wallheight, check_side());
		get()->x++;
	}
}
