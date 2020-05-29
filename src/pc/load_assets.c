#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#define SAFE_FREE(x) free(x); x = NULL;

ALIGNED8 u8 *goomba_seg8_texture_08019530;
ALIGNED8 u8 *goomba_seg8_texture_08019D30;
ALIGNED8 u8 *goomba_seg8_texture_0801A530;

u8* get_u8_array_from_file(const char* filename)
{
	FILE *fileptr;
	u8 *buffer;
	size_t filelen;

	fileptr = fopen(filename, "rb");
	fseek(fileptr, 0, SEEK_END);    
	filelen = ftell(fileptr);       
	rewind(fileptr);                

	buffer = (u8*) malloc(filelen * sizeof(u8));
	fread(buffer, filelen, 1, fileptr);
	fclose(fileptr);

	printf("\nFILE: %s\n", filename);
	for (int i = 0; i < filelen; i++) {
        printf(" %02x", buffer[i]);
    }
    printf("\n");

	return buffer;
}

void load_all_assets()
{
	goomba_seg8_texture_08019530 = get_u8_array_from_file("actors/goomba/goomba_body.rgba16");
	goomba_seg8_texture_08019D30 = get_u8_array_from_file("actors/goomba/goomba_face.rgba16.inc.c");
	goomba_seg8_texture_0801A530 = get_u8_array_from_file("actors/goomba/goomba_face_blink.rgba16.inc.c");
}

void free_all_assets()
{
	SAFE_FREE(goomba_seg8_texture_08019530);
	SAFE_FREE(goomba_seg8_texture_08019D30);
	SAFE_FREE(goomba_seg8_texture_0801A530);
}