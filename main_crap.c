#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "def.h"
#include "structs.h"

#define MAX_TILE_SET_X 20
#define MAX_TILE_SET_Y	15

#define TILE_SIZE  32
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480



//SDL_Surface  *p_window_surface = NULL;
//SDL_Surface  *p_loaded_image_surface = NULL;
SDL_Renderer *p_renderer = NULL;
SDL_Window *p_window = NULL;
SDL_Event event;

typedef struct{
    SDL_Texture *texture_map_background;
    SDL_Texture *texture_tile;
    SDL_Texture *texture_tile_1;


int tileset_0[MAX_TILE_SET_X][MAX_TILE_SET_Y];
int tileset_1[MAX_TILE_SET_X][MAX_TILE_SET_Y];


}map;

typedef struct{

    SDL_Texture *texture_player_sprite;


}player;

int tile_numb;

sprite sprite_0;
player player_0;
map map_0;

int skull_pos_x = 0;
int skull_pos_y = 0;
int tile_pos = 0;
uint32_t timer;


void load_map_text(map *map)
{
    FILE *fp;
    fp = fopen("map/map_0.txt","r");
    if(fp == NULL) printf("can't open map file\n");

    for(int y=0; y<MAX_TILE_SET_Y;y++)
        {
              for(int x=0; x<MAX_TILE_SET_X;x++)fscanf(fp,"%i",&map_0.tileset_0[x][y]);


      }
        printf("map file loaded into array");
   }

SDL_Texture *load_image(char *name)
{
	SDL_Surface *loaded_image = NULL;
	SDL_Texture *texture = NULL;
	loaded_image = IMG_Load(name);

		if(loaded_image != NULL)
		{
			texture = SDL_CreateTextureFromSurface(p_renderer, loaded_image);
			SDL_FreeSurface(loaded_image);
			loaded_image = NULL;
		}

		else
			printf("png image can't be loaded");

	return texture;
}
void draw_map_tile(void)
{


    for (int y = 0; y < MAX_TILE_SET_Y; y++)
	{
		for (int x = 0; x < MAX_TILE_SET_X; x++)
		{
            if(map_0.tileset_0[x][y])
                {
                    SDL_Rect dest;
                    dest.x = x*TILE_SIZE;
                    dest.y =y*TILE_SIZE;
                    dest.w = TILE_SIZE;
                    dest.h = TILE_SIZE;

                    SDL_Rect src;
                      src.x =(map_0.tileset_0[x][y]-1) * TILE_SIZE;
                    src.y = 3 * TILE_SIZE;//(map_0.tileset_0[x][y]-1) * TILE_SIZE;
                    src.w = TILE_SIZE;
                    src.h = TILE_SIZE;
                      SDL_RenderCopy(p_renderer,map_0.texture_tile, &src, &dest);

            }
		}
	}


}
void draw_tile(map * map, char tile)
{
	/* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = 0;
	dest.y =0;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

    //pass value to select the tile

    switch(tile)
    {
    case 0:
      src.x =160;
	src.y = 0;
	break;

	case 1:
        src.x =TILE_HEARTB_LOC_X;
	src.y = TILE_HEARTB_LOC_Y;
	break;

	case 2:
    src.x =TILE_BAT_LOC_X;
	src.y = TILE_BAT_LOC_Y;
	break;



    }

	src.w = TILE_SIZE;
	src.h = TILE_SIZE;


            for(int i=0; i<TILE_SIZE  * 10;i++){
            SDL_RenderCopy(p_renderer,map->texture_tile, &src, &dest);
            dest.x += TILE_SIZE;
            }


}
void draw_player(player *player)
{
    	SDL_Rect dest;

	dest.x = 0;
	dest.y = 64;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

	src.x =64;
	src.y = 0;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;
	SDL_RenderCopy(p_renderer,player->texture_player_sprite, &src, &dest);


}
char init_SDL(void)
{
    char ok = 1;

    printf("synth_test\n");
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("can't open SDL\n");
        ok = 0;
    }
     else    p_window = SDL_CreateWindow("synth",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                 640,
                480,
                 SDL_WINDOW_RESIZABLE
                 );

     if(!p_window){
        printf("can't open Window\n");
        ok = 0;
     }

        //render association
         p_renderer = SDL_CreateRenderer(p_window,-1, SDL_RENDERER_ACCELERATED);
     //   SDL_Surface *p_image  =  IMG_Load("img\\skull_map_neg.png");
/*
        if(!p_image){
        printf("no image\n");
        ok = 0;
        }
 //  map_0.texture_map_background = SDL_CreateTextureFromSurface(p_renderer, p_image);
   */ SDL_RenderCopy(p_renderer, map_0.texture_map_background, NULL, NULL);

//       SDL_FreeSurface(p_image);



    return ok;
}
void draw_screen(void)
{

SDL_Rect rect;
/*
SDL_GetWindowSize(p_window,&rect.w,&rect.h);
SDL_SetWindowSize(p_window, rect.w, rect.h);
*/

//background
SDL_RenderCopy(p_renderer, map_0.texture_map_background, NULL, NULL);
//draw_tile(&map_0,tile_numb);
draw_map_tile();
//draw_player(&player_0);
SDL_RenderPresent(p_renderer);


}
int main(int argc, char *argv[])
{

    if(!init_SDL())  printf("init failed\n");


 map_0.texture_map_background =   load_image("img\\skull_neg.png");
 map_0.texture_tile = load_image("img\\futur_tile.png");
  map_0.texture_tile_1 = load_image("img\\futur_tile.png");

 player_0.texture_player_sprite = load_image("img\\girl.png");
 load_map_text(&map_0);
 SDL_RenderPresent(p_renderer);



/*
map_0.tileset_0[0][3] = 1;
map_0.tileset_0[3][4] = 1;
map_0.tileset_0[4][4] = 1;
map_0.tileset_0[5][0] = 1;
map_0.tileset_0[0][0] = 1;

map_0.tileset_0[8][8] = 1;
map_0.tileset_0[10][9] = 1;
map_0.tileset_0[5][2] = 1;
map_0.tileset_0[7][3] = 1;
map_0.tileset_0[6][14] = 1;
map_0.tileset_0[4][16] = 1;
map_0.tileset_0[14][8] = 1;
map_0.tileset_0[19][12] = 1;*/
/*
for(int y=14; y>11; y--)
{
    for(int x=0; x<MAX_TILE_SET_X; x++)
    {
        map_0.tileset_0[x][y] = 1;
    }
}*/

    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {

                case SDL_QUIT:
                    exit(0);
                break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            exit(0);
                        break;

                        case SDLK_a:
                  tile_numb += TILE_SIZE;
                            if(skull_pos_x >= 448) skull_pos_x = 0;
                             break;

                        case SDLK_LEFT:
                         tile_numb += 32;
                              if(skull_pos_x >= 480) skull_pos_x = 0;

                                break;

                                      case SDLK_UP:
                                    tile_numb++;
                                        if(tile_numb>2) tile_numb = 0;

                                break;

                                          case SDLK_DOWN:
                                        tile_numb--;
                                        if(tile_numb<0) tile_numb = 2;

                                break;

                                       case SDL_WINDOWEVENT_RESIZED:
                                            break;
                        default:
                        break;
                    }
                break;

        default:
        break;
		}





     // timer++;


    }


   draw_screen();



}
SDL_DestroyWindow(p_window);
SDL_DestroyRenderer(p_renderer);
SDL_Quit();
return 0;
}
