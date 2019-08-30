/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:05:15 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/29 21:21:37 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef unsigned char	uint8;
typedef char			sint8;

typedef unsigned short int	uint16;
typedef short int			sint16;

typedef unsigned int	uint32;
typedef int				sint32;

typedef unsigned long int	uint64;
typedef long int			sint64;

typedef float			f32;
typedef double			f64;

typedef struct s_bitmap_header
{
    uint16 file_type;
    uint32 file_size;
    uint16 reserved1;
    uint16 reserved2;
    uint32 bitmap_offset;
    uint32 size;
    sint32 width;
    sint32 height;
    uint16 planes;
    uint16 bits_per_pixel;
    uint32 compression;
    uint32 size_of_bitmap;
    sint32 horiz_resolution;
    sint32 vert_resolution;
    uint32 colors_used;
    uint32 colors_important;
uint32 red_mask;
    uint32 green_Mask;
    uint32 blue_mask;
}			t_bitmap_header;

struct loaded_bitmap
{
    void		*memory;
    sint32	width;
    sint32	height;
    sint32	pitch;
};

struct entire_file
{
    uint32 ContentsSize;
    void *Contents;
};
