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

typedef struct s_bitmap_header
{
    uint16 file_type; // 0;
		uint32 file_size; // 2;
		uint16 reserved1; // 6;
		uint16 reserved2; // 8;
		uint32 bitmap_offset; // 10;
    uint32 size;          //14;
    sint32 width;         // 18;
		sint32 height;        //22;
		uint16 planes;        //26;
    uint16 bits_per_pixel; // 28;
    uint32 compression;     //30;
    uint32 size_of_bitmap;  // 34;
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
