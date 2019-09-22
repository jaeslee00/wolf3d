/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:43:55 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/21 21:00:00 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "bmp_reader.h"

t_s32		read_all(t_s32 fd, t_u8 *data, t_s32 size)
{
	t_s32	read_bytes;
	t_s32	ret;

	read_bytes = 0;
	while (((ret = read(fd, data + read_bytes, size - read_bytes)) > 0))
		read_bytes = read_bytes + ret;
	//printf("read_bytes = %d\n", read_bytes);
	if (ret <= 0)
		return (ret);
	return (read_bytes + ret);
}

t_bitmap_header get_header(t_u8 *mem)
{
	t_bitmap_header header;
	
	ft_memcpy(&header.file_type, &mem[0], sizeof(t_u16));
	if (header.file_type != 19778)
		               is_alloc(NULL, NULL, -4);
	ft_memcpy(&header.file_size, &mem[2], sizeof(t_u32));
	ft_memcpy(&header.reserved1, &mem[6], sizeof(t_u16));
	ft_memcpy(&header.reserved2, &mem[8], sizeof(t_u16));
	ft_memcpy(&header.bitmap_offset, &mem[10], sizeof(t_u32));
	ft_memcpy(&header.size, &mem[14], sizeof(t_u32));
	ft_memcpy(&header.width, &mem[18], sizeof(t_s32));
	ft_memcpy(&header.height, &mem[22], sizeof(t_s32));
	ft_memcpy(&header.size_of_bitmap, &mem[34], sizeof(t_s32));
	//printf("file size = %d, height = %d, width - %d header size %d offset %d\n", header.file_size, header.height, header.width, header.size, header.bitmap_offset);
	return (header);
}

void	palette(t_u32 *img, t_palette *p, t_u32 size)
{
	t_u32 i;
	t_u32 j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < p->size)
		{
			if (img[j] == p->pal[i])
			{
				j++;
				break;
			}
			i++;
		}
		if (i == p->size)
		{
			p->pal[i] = img[j];
			p->size++;
		}
		j++;
	}
}

void		data_to_img(t_bitmap_header b, t_u8 *d, t_texture *tex, t_s32 o)
{
	t_s32 i;
	t_s32 j;
	t_s32 k;
	t_s32 l;
	
	l = b.height - 1;
	j = 0;
	while (j < b.height)
	{
		i = 0;
		k = o;
		while (i < b.width + o)
		{
			tex->data[i + j * b.width] = d[k + (l * b.width * 3)] |
				d[(k + 1) + (l * b.width * 3)] << 8 | d[(k + 2) +
				(l * b.width * 3)] << 16;
			if (tex->data[i + j * b.width] == 0)
				tex->data[i + j * b.width] = 1;
			i++;
			k += 3;
		}
		o -= b.width % 4;
		l--;
		j++;
	}
}

t_texture	read_bmp(const t_s8 *filename, t_wolf *wolf, t_palette *pal)
{
	t_bitmap_header bitmap;
	t_u8		data[3 * 120 * 120];
	t_s32		fd;
	t_u8		header[54];
	t_texture	tex;

	ft_bzero(data, sizeof(data));
	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		read(fd, header, 54);
		bitmap = get_header(header);
		tex.width = bitmap.width;
		tex.height = bitmap.height;
		tex.size = 3 * tex.width * tex.height;
		is_alloc(tex.data = (t_u32*)ft_mem(&wolf->mem, tex.width * tex.height * sizeof(t_u32)), wolf, -1);
		read_all(fd, data, tex.size);
		data_to_img(bitmap, &data[0], &tex, (bitmap.height - 1) * (bitmap.width % 4));
		palette(tex.data, pal, (bitmap.height * bitmap.width) - 1);
	}
	else
		ft_bzero(&tex, sizeof(tex));
	return (tex);
}