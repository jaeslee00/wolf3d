/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:43:55 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/30 15:04:39 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "bmp_reader.h"

sint32		read_all(sint32 fd, uint8 *data, sint32 size)
{
	sint32	read_bytes;
	sint32	ret;

	read_bytes = 0;
	while (((ret = read(fd, data + read_bytes, size - read_bytes)) > 0))
		read_bytes = read_bytes + ret;
	printf("read_bytes = %d\n", read_bytes);
	if (ret <= 0)
		return (ret);
	return (read_bytes + ret);
}

t_bitmap_header get_header(uint8 *mem)
{
	t_bitmap_header header;
	
	ft_memcpy(&header.file_type, &mem[0], sizeof(uint16));
	ft_memcpy(&header.file_size, &mem[2], sizeof(uint32));
	ft_memcpy(&header.reserved1, &mem[6], sizeof(uint16));
	ft_memcpy(&header.reserved2, &mem[8], sizeof(uint16));
	ft_memcpy(&header.bitmap_offset, &mem[10], sizeof(uint32));
	ft_memcpy(&header.size, &mem[14], sizeof(uint32));
	ft_memcpy(&header.width, &mem[18], sizeof(sint32));
	ft_memcpy(&header.height, &mem[22], sizeof(sint32));
	ft_memcpy(&header.size_of_bitmap, &mem[34], sizeof(sint32));
	printf("file size = %d, height = %d, width - %d header size %d offset %d\n", header.file_size, header.height, header.width, header.size, header.bitmap_offset);
	return (header);
}

t_texture	read_bmp(const sint8 *filename, t_wolf *wolf)
{
	sint32	offset;
//	uint32	temp;
	t_bitmap_header bitmap;
	uint8		data[3 * 120 * 120];
	sint32		fd;
	uint8		header[54];
	t_texture	tex;
	sint32 i;
	sint32 j;
//	sint32 k;

	offset = 0;
	ft_bzero(data, sizeof(data));
	/*
 TODO(viccarau): Everything will be read at once, then the reading of the image is going to start
 at the begining of bitmap.offset, I need to reverse the uint8 data, and then read the image from
 the end;
 */
	fd = open(filename, O_RDONLY);
	read(fd, header, 54);
	bitmap = get_header(header);
	tex.width = bitmap.width;
	tex.height = bitmap.height;
	tex.size = 3 * tex.width * tex.height;
	is_alloc(tex.data = (uint32*)ft_mem(&wolf->mem, tex.width * tex.height * sizeof(uint32)), wolf, -1);
	read_all(fd, data, tex.size);
	i = (bitmap.height * bitmap.width) - 1;
	j = 0;
	while (i >= 0 + offset)
	{
		tex.data[i] = data[j] | data[j + 1] << 8 | data[j + 2] << 16;
		i--;
		j += 3;
		if (bitmap.width % 4 != 0)
			if (i % bitmap.width == 0)
		{
			j++;
			offset++;
		}
	}
/*	i = 0;
	while (i < bitmap.height)
	{
		j = 0;
		k = bitmap.width;
		while (j < (bitmap.width / 2))
		{
			//printf("i %d, j %d, k %d\n", i, j, k);
			temp = tex.data[j + i * bitmap.height];
			tex.data[j + i * bitmap.height] = tex.data[k + i * bitmap.height];
			tex.data[k + i * bitmap.height] = temp;
			j++;
			k--;
		}
		i++;
	}*/
	return (tex);
}
