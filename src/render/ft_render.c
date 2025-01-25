/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/25 01:13:39 by asagymba         ###   ########.fr       */
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
 * Thanks a lot to @3DSage.
 * TODO: Doc
 */
static void	ft_draw_line(struct s_data *data, struct s_img *img,
		struct s_ray ray, int x_offset)
{
	const double		fix_fisheye = data->player_angle.angle - ray.angle;
	double				line_height;
	double				line_offset;
	int					i;
	int					j;
	const struct s_rgb	red = (struct s_rgb){255, 255, 0, true};

	ray.distance = ray.distance * cos(fix_fisheye);
	line_height = (((int)ft_strlen(data->map->content) * (int)ft_lstsize(data->map))
			* BLOCK_Y) / ray.distance;
	if (line_height > BLOCK_Y)
		line_height = BLOCK_Y;
	line_offset = WIN_Y / 2 - line_height / 2;
	i = 0;
	while (i < line_height)
	{
		j = 0;
		while (j < WIN_X / FOV)
			ft_pixel_put_on_image(img, x_offset + j++, line_offset + i, &red);
		i++;
	}
}

/**
 * Draws walls (use textures from \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image to where draw them.
 */
static void	ft_draw_walls(struct s_data *data, struct s_img *img)
{
	struct s_ray	rays[FOV];
	const double	gap_between_rays = DEGREE;
	int				i;

	(void)ft_memset(rays, 0, sizeof(struct s_ray) * FOV);
	ft_horizontal_ray_cast(data, rays, FOV, gap_between_rays);
	ft_vertical_ray_cast(data, rays, FOV, gap_between_rays);
	i = 0;
	while (i < FOV)
	{
		ft_draw_line(data, img, rays[i], i * WIN_X / FOV);
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
	printf("%d %d (%d %d): %c | %f\n", data->player.x, data->player.y,
		data->player.x / BLOCK_X, data->player.y / BLOCK_Y,
		ft_get_map_row(data->map, data->player.y
			/ BLOCK_Y)[data->player.x / BLOCK_X], data->player_angle.angle);
	(void)mlx_put_image_to_window(data->conn, data->win, img.img,
		BEGINNING, BEGINNING);
	(void)mlx_destroy_image(data->conn, img.img);
	return (0);
}
