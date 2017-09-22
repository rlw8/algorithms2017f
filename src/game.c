#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

typedef struct
{
	int width;
}Brick;

typedef struct
{
	void *data;
	int priority;
}PriorityQueue;

PriorityQueue p_queue[20];

void p_queue_in(Brick *stuff, PriorityQueue *queue);

void p_queue_in(Brick *stuff, PriorityQueue *queue)
{
	
	int i = 0;
	if (!stuff || !queue)return;
	while (stuff != NULL)
	{
		queue[i].priority = stuff[i].width;
		i++;
	}
}

void p_queue_sort(PriorityQueue *list, int n);

void swap_array(int *num1, int *num2);

void p_queue_sort(PriorityQueue *list, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (list[j].priority > list[j + 1].priority)
			{
				swap_array(list[j].priority, list[j + 1].priority);
			}
		}
	}
}

void swap_array(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
/*
typedef struct
{
	void *data;
	size_t numElements;
	size_t elementSize;
}PriorityQueue;

PriorityQueue *pq_new(size_t elementSize)
{
	PriorityQueue p_queue;
	p_queue.elementSize;
}

void pq_delete(PriorityQueue *pq);
void *pq_delete_max(PriorityQueue *pq);
void pq_insert(PriorityQueue *pq, void *data, int priority);
*/


void draw_stack(Sprite *brick, Vector2D start, Brick *bricklist, unsigned int count)
{
	unsigned int i, j;
	int brickheight = 32;
	int brickwidth = 32;
	Vector2D drawPosition;
	if (!brick)return;
	if (!bricklist)return;
	for (i = 0; i < count; i++)
	{
		//vertical draw
		drawPosition.x = start.x - ((bricklist[i].width * brickwidth) / 2);
		drawPosition.y = start.y - ((i + 1) * brickheight);
		for (j = 0; j < bricklist[i].width; j++)
		{
			//horizontal draw
			drawPosition.x += brickwidth;
			gf2d_sprite_draw(
				brick,
				drawPosition,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				0);
		}
	}
}


int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite, *brick;
	static Brick bricklist[] =
	{
		{ 2 },
		{ 7 },
		{ 1 },
		{ 5 },
		{ 14 },
		{ 9 },
		{ 13 },
		{ 24 },
		{ 16 },
		{ 22 }
	};

	p_queue_in(bricklist, p_queue);

	p_queue_sort(p_queue, 10);













	int mx, my;
	float mf = 0;
	Sprite *mouse;
	Vector4D mouseColor = { 0,0,255,200 };

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"gf2d",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(17);
	gf2d_sprite_init(1024);
	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/

	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	brick = gf2d_sprite_load_all("images/brick.png", 32, 32, 16);
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	/*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
										   /*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;


		gf2d_graphics_clear_screen();// clears drawing buffers
									 // all drawing should happen betweem clear_screen and next_frame
									 //backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));

		draw_stack(brick, vector2d(600, 700), p_queue, 10);

		//UI elements last
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
		slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second());
	}
	slog("---==== END ====---");
	return 0;
}
/*eol@eof*/