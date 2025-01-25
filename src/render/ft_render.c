/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/25 21:03:06 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <mlx.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utils.h>

#define BEGINNING	0

/**
 * Draws a ceiling and floor (defined in \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image where to draw them.
 */
static void	ft_draw_ceiling_and_floor(struct s_data *data,
		struct s_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height / 2)
	{
		j = 0;
		while (j < img->width)
			ft_pixel_put_on_image(img, j++, i, &data->colors[COLOR_CEILING]);
		i++;
	}
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
			ft_pixel_put_on_image(img, j++, i, &data->colors[COLOR_FLOOR]);
		i++;
	}
}

/**
 * Draw a line on \p img based on cast \p ray values.
 * Thanks a lot to @3DSage.
 * @param	data		cub3D's data.
 * @param	img			Image where to draw al ine.
 * @param	ray			Cast ray.
 * @param	x_offset	On which x to start the drawing process.
 */
static void	ft_draw_line(struct s_data *data, struct s_img *img,
		struct s_ray ray, int x)
{
	struct s_draw_line	draw_line_data;
	int					j;
	const struct s_rgb	red = (struct s_rgb){255, 0, 0, true};

	draw_line_data.fix_fisheye = ft_initialize_angle(data->player_angle.angle
			- ray.angle);
	ray.distance = ray.distance * cos(draw_line_data.fix_fisheye);
	draw_line_data.line_height = WIN_Y * BLOCK_Y / ray.distance;
	if (draw_line_data.line_height > WIN_Y)
		draw_line_data.line_height = WIN_Y;
	draw_line_data.line_offset = WIN_Y / 2 - draw_line_data.line_height / 2;
	j = 0;
	while (j < draw_line_data.line_height)
		ft_pixel_put_on_image(img, x, draw_line_data.line_offset + j++, &red);
}

/**
 * Draws walls (use textures from \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image to where draw them.
 */
static void	ft_draw_walls(struct s_data *data, struct s_img *img)
{
	struct s_ray	rays[WIN_X];
	const double	gap_between_rays = DEGREE * ((FOV * 1.0f) / WIN_X);
	int				i;

	(void)ft_memset(rays, 0, sizeof(struct s_ray) * WIN_X);
	ft_horizontal_ray_cast(data, rays, WIN_X, gap_between_rays);
	ft_vertical_ray_cast(data, rays, WIN_X, gap_between_rays);
	i = 0;
	while (i < WIN_X)
	{
		ft_draw_line(data, img, rays[i], i);
		i++;
	}
}

int	ft_render(struct s_data *data)
{
	struct s_img	img;

	img.img = mlx_new_image(data->conn, WIN_X, WIN_Y);
	if (img.img == NULL)
	{
		if (errno == 0)
			errno = EACCES;
		return (perror("cub3D"), ft_mlx_exit(data, EXIT_FAILURE), -1);
	}
	img.width = WIN_X;
	img.height = WIN_Y;
	img.img_pixels = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.size_line, &img.endianness);
	ft_draw_ceiling_and_floor(data, &img);
	ft_draw_walls(data, &img);
	(void)mlx_put_image_to_window(data->conn, data->win, img.img,
		BEGINNING, BEGINNING);
	(void)mlx_destroy_image(data->conn, img.img);
	return (0);
}
