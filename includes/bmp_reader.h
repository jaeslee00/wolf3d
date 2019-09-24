/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:05:15 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/30 13:05:32 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct	s_bitmap_header
{
	t_u16	file_type;
	t_u32	file_size;
	t_u16	reserved1;
	t_u16	reserved2;
	t_u32	bitmap_offset;
	t_u32	size;
	t_s32	width;
	t_s32	height;
	t_u16	planes;
	t_u16	bits_per_pixel;
	t_u32	compression;
	t_u32	size_of_bitmap;
	t_s32	horiz_resolution;
	t_s32	vert_resolution;
	t_u32	colors_used;
	t_u32	colors_important;
	t_u32	red_mask;
	t_u32	green_Mask;
	t_u32	blue_mask;
}				t_bitmap_header;
