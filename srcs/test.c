#include <stdio.h>
#include <string.h>

typedef int sint32;
typedef float f32;

void    merge(f32 *a, sint32 left, sint32 right, sint32 mid)
{
    sint32	size_left;
    sint32	size_right;
    f32		arr_left[20];
	f32		arr_right[20];
	sint32	idx_left;
	sint32	idx_right;
	sint32	idx_merge;

    size_left = mid - left + 1;
    size_right = right - mid;

	sint32 i;
	i = 0;
	while (i < size_left)
	{	
		arr_left[i] = a[left + i];
		i++;
	}
	i = 0;
	while (i < size_right)
	{	
		arr_right[i] = a[mid + 1 + i];
		i++;
	}
	idx_left = 0;
	idx_right = 0;
	idx_merge = left;
	while (idx_left < size_left && idx_right < size_right)
	{
		if (arr_left[idx_left] <= arr_right[idx_right])
		{
			a[idx_merge] = arr_left[idx_left];
			idx_merge++;
			idx_left++;
		}
		else
		{
			a[idx_merge] = arr_right[idx_right];
			idx_merge++;
			idx_right++;
		}
	}
	while (idx_left < size_left)
	{
		a[idx_merge] = arr_left[idx_left];
		idx_merge++;
		idx_left++;		
	}
	while (idx_right < size_right)
	{
		a[idx_merge] = arr_right[idx_right];
		idx_merge++;
		idx_right++;		
	}
}

void    merge_sort(f32 *a, sint32 left, sint32 right)
{
	sint32  mid;

    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, right, mid);
    }
}

int main()
{
    f32 a[8] = {3.f, 4.f, 7.f, 1.f, 5.f, 10.f, 9.f};
    merge_sort(a, 0, 6);
	for(int i=0; i < 8; i++)
		printf("%f\n", a[i]);
    return (1);
}