/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:56:57 by root              #+#    #+#             */
/*   Updated: 2025/01/21 16:09:42 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <libft.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
/**
 * For t_args.
 */
/* Textures and their indexes. */
# define TEXTURES_SIZE 4
# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3
/* Colors and their indexes. */
# define COLORS_SIZE 2
# define COLOR_FLOOR 0
# define COLOR_CEILING 1

/**
 * For system crashes: malloc, write...
 */
# define FATAL_ERROR -1
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"
// parameter which is not he map and we can't identify 
# define INV_PAR 1
// one of parameter is duplicated
# define DUP_PAR 2
/**
 * ----------------------------------------------------------------------------
 * Structures.
 * ----------------------------------------------------------------------------
 */
typedef struct s_rgb
{
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
}					t_rgb;

/**
 * Every node of \ref map contains a string (a row) of a map.
 * Parser will save information here.
 */
typedef struct s_args
{
	int				map_info_added;
	char			*textures[TEXTURES_SIZE];
	t_rgb			colors[COLORS_SIZE];
	t_list			*map;
}					t_args;

/**
 * Mainly MLX data, but also player's position,
 * floor's and ceiling's colors, map, etc.
 */
typedef struct s_data
{
	void	*conn;
	void	*winn;
	void	*textures[TEXTURES_SIZE];
}	t_data;

#endif /* CUB3D_H */
