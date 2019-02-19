#include "SDL2/SDL.h"
#include <stdio.h>
#include "scene_builder.h"
#include "renderer.h"
#include "texture.h"
#include "color.h"

SDL_Window *window;
SDL_Renderer *renderer;
int done;

typedef struct {
	renderer_t *renderer;
	scene_t *scene;
	vec3_t from, to;
	float l,r,t,b,f,n;
	cRGB_t  bgcolor;
} render_context_t;

render_context_t * render_ctx;

mat3_t * rxp, *rxm, *ryp, *rym;

void render_scence_again()
{
	//render_context_t * rctx = (render_context_t *)IupGetGlobal("RCTX");
	renderer_t * renderer = render_ctx->renderer;
	camera_t * curcam = &renderer->camera;
	scene_t * scene = render_ctx->scene;
	vec3_t * from = &render_ctx->from;
	vec3_t * to = &render_ctx->to;
	//config_camera_perspective(&renderer->camera, from, to, 
	//				rctx->l, rctx->r, rctx->t, rctx->b, rctx->n, rctx->f);
	//setviewport(curcam,l,r,t,b,near,far);
	camera_lookAt_perspective(curcam, from, to);
	//createProjectionPerspective(curcam, l, r, t, b, near, far);
	mat4_mul_dest(&curcam->transformation ,&curcam->view, &curcam->projection);
	renderer_clear_frame(renderer);
	render_scene(renderer, scene);	
}


static void 
create_test_renderer()
{
	  render_ctx = malloc(sizeof(render_context_t));
	  render_ctx->bgcolor = (cRGB_t){0.0f, 0.0f, 0.0f};
	  render_ctx->from = (vec3_t){0.f, 0.f, 2.f };
	  render_ctx->to = (vec3_t){0.f, 0.f, 0.f};
	  render_ctx->renderer = renderer_new(512, 512, &render_ctx->bgcolor, 2);
	  render_ctx->renderer->projection = RP_PERSPECTIVE;
	  float view = 2.f;
	  render_ctx->l = -view;
	  render_ctx->r = view;
	  render_ctx->t = view;
	  render_ctx->b = -view;
	  render_ctx->f = 5.f;
	  render_ctx->n = 1.f;
	  scene_t * scene;
	  //scene = scene_create_triangle();
	  scene = scene_create_test_all();
	  //scene = scene_create_tree();
	  //scene = scene_create_test();
	  //scene = scene_create_test_point_raster();
	  render_ctx->scene = scene;
	  //IupSetGlobal("RCTX", (void*) render_ctx);
	  config_camera_perspective(&render_ctx->renderer->camera, &render_ctx->from, &render_ctx->to, 
					render_ctx->l, render_ctx->r, render_ctx->t, render_ctx->b, render_ctx->n, render_ctx->f);
	  render_scence_again();
	  rxp = create_rot_x_mat(1.0011f);
	  rxm = create_rot_x_mat(-1.0011f);
	  ryp = create_rot_y_mat(1.0011f);
	  rym = create_rot_y_mat(-1.0011f);
}

static void
cleanup_renderer() {
	printf("cleanup renderer\n");
	renderer_free(render_ctx->renderer);
	free_scene(render_ctx->scene);
	free(render_ctx);
	free(rxp);
	free(rxm);
	free(ryp);
	free(rym);
}

void
DrawFrameBuffer(SDL_Renderer * renderer)
{
	renderer_t * _renderer = render_ctx->renderer;
	unsigned int bi=0, samplestart;
	int i, j, cj, imgW = _renderer->imgWidth, 
				  imgH = _renderer->imgHeight;
	const int us = _renderer->used_samples, bw = _renderer->bufWidth;
	cRGB_t fc;
	cRGB_t * fb = _renderer->frameBuffer;
	cRGB_t * c = fb;

	unsigned int maxidx = imgW*imgH;
	unsigned int pixeldata[maxidx];
	unsigned int pxidx = 0;
	for (j = imgH; j--; )
    {
	  bi = j * bw;
	  //cj = ((imgH-1) - j);
	  for (i = imgW; i--; )
	  {
		fc.r = 0.f, fc.g = 0.f, fc.b = 0.f;
		samplestart = bi + (i*us);
		switch (us) {
			case 16:
				c = fb + samplestart + 15;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 15:
				c = fb + samplestart + 14;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 14:
				c = fb + samplestart + 13;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 13:
				c = fb + samplestart + 12;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 12:
				c = fb + samplestart + 11;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 11:
				c = fb + samplestart + 10;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 10:
				c = fb + samplestart + 9;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 9:
				c = fb + samplestart + 8;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 8:
				c = fb + samplestart + 7;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 7:
				c = fb + samplestart + 6;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 6:
				c = fb + samplestart + 5;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 5:
				c = fb + samplestart + 4;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 4:
				c = fb + samplestart + 3;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 3:
			    c = fb + samplestart + 2;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 2:
				c = fb + samplestart + 1;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
			case 1:
				c = fb + samplestart;
				fc.r += c->r; fc.g += c->g; fc.b += c->b;
				break;
		}
		SDL_SetRenderDrawColor(renderer, (unsigned char)(fc.r * 255.f), 
										 (unsigned char)(fc.g * 255.f), 
										 (unsigned char)(fc.b * 255.f), 
										 0xFF);
		SDL_RenderDrawPoint(renderer, i, j);
	  }
   }

}

static int render_view_rot(mat3_t * rotmat)
{
	vec3_t * from = &render_ctx->from;
	mat_vec_mul_3(rotmat, from);
	
	render_scence_again();
}

static int render_view_zoom(float zoom)
{
	vec3_t * from = &render_ctx->from;
	vec3_t normalized;
	vec3_normalize_dest( &normalized, from);
	//vec3_mul(&normalized, zoom);
	normalized.x *= zoom;
	normalized.y *= zoom;
	normalized.z *= zoom;
	//vec3_add(from, &normalized);
	from->x += normalized.x;
	from->y += normalized.y;
	from->z += normalized.z;
	
	render_scence_again();
}

void
loop()
{
    SDL_Event e;
	while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            done = 1;
            return;
        }

        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_x)) {

            return;
        }

        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_y)) {

      	   mat3_t *rxm_ = create_rot_x_mat(-88.f);
           render_view_rot(rxm_);
           free(rxm_);
           DrawFrameBuffer(renderer);
           SDL_UpdateWindowSurface(window);
		   return;
        }
		
        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_x)) {

        	mat3_t * rym_ = create_rot_y_mat(-88.f);
        	render_view_rot(rym_);
        	free(rym_);
        	DrawFrameBuffer(renderer);
        	SDL_UpdateWindowSurface(window);
            return;
        }

		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_UP)) {
            printf("up\n");
			render_view_rot(rxp);
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_DOWN)) {
            printf("down\n");
			render_view_rot(rxm);
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_LEFT)) {
            printf("left\n");
			render_view_rot(rym);
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RIGHT)) {
            printf("right\n");
			render_view_rot(ryp);
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_PLUS)) {
            printf("zoom in\n");
			render_view_zoom(0.01f);	
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_MINUS)) {
            printf("zoom out\n");
			render_view_zoom(-0.01f);
			DrawFrameBuffer(renderer);
			SDL_UpdateWindowSurface(window);
            return;
        }
		
    }
    
    /* Got everything on rendering surface,
       now Update the drawing image on window screen */
    SDL_UpdateWindowSurface(window);
}

int
main(int argc, char *argv[])
{
    SDL_Surface *surface;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }

    /* Create window and renderer for given surface */
    window = SDL_CreateWindow("3D Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, 0);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return 1;
    }
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return 1;
    }

    /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    /* Draw the Image on rendering surface */
    done = 0;
	create_test_renderer();
	DrawFrameBuffer(renderer);
    while (!done) {
        loop();
    }
	cleanup_renderer();
    SDL_Quit();
    return 0;
}
