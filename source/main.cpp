
#include <cstdint>
#include "math.hpp"
#include "renderer.hpp"
#include "video.hpp"
#include "input.hpp"
#include <glm/glm.hpp>

int main(int, char**)
{
	// create surface and its texture
	VIDEO_Surface* surface = VIDEO_InitVideo();
	if (surface == NULL) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		printf("Failed to init Allegro");
		return 1;
	}
	
	// load images to sample
	VIDEO_Surface* goober = VIDEO_ImgLoad("./assets/goober.bmp");
	VIDEO_Surface* crate = VIDEO_ImgLoad("./assets/crate.bmp");
	
	// rendering structs
	Renderer3D renderer3d;
	Target target = surface;
	Camera3D camera{ glm::vec3(3.5f, 1.5f, -2.0f), 45.0f, -20.0f };
	Screen screen{ (float)surface->w, (float)surface->h, 60.0f };
	
	// for calculating delta time
	//Uint64 time_now = SDL_GetPerformanceCounter();
	//Uint64 time_prev = time_now;
	unsigned int time_now = INPUT_time_now;
	unsigned int time_prev = time_now;
	
	// global variables
	float sensitivity = 0.2f;
	
	// game state
	float spike_x = 0.0f;
	
	// load models
	Model3D floor_model;
	LoadModel("./assets/floor.txt", floor_model);
	
	Model3D triangle_model;
	LoadModel("./assets/triangle.txt", triangle_model);
	
	Model3D spike_model;
	LoadModel("./assets/spike.txt", spike_model);
	
	Model3D crate_model;
	LoadModel("./assets/crate.txt", crate_model);
	
	INPUT_Init();
	
	// main loop
	static int mX, mY;

	for (bool running = true; running;)
	{
		get_mouse_mickeys(&mX, &mY);
		camera.Turn(
			-sensitivity * (float)mX,
			-sensitivity * (float)mY
		);
		
		if (key[KEY_ESC]) {
			running = false;
			break;
		}
		// process events
		/*for (SDL_Event event{}; running && SDL_PollEvent(&event);)
		{
		switch (event.type)
		{
		    case SDL_QUIT:
		        running = false;
		        break;
		    
		    case SDL_MOUSEMOTION:
		        if (SDL_GetRelativeMouseMode())
		        {
		            camera.Turn(
		                -sensitivity * (float)event.motion.xrel,
		                -sensitivity * (float)event.motion.yrel
		            );
		        }
		        break;
		    
		    case SDL_MOUSEBUTTONDOWN:
		        if (event.button.button == SDL_BUTTON_LEFT)
		        {
		            SDL_SetRelativeMouseMode(SDL_TRUE);
		            SDL_ShowCursor(SDL_FALSE);
		        }
		        break;
		    
		    case SDL_KEYDOWN:
		        if (event.key.keysym.sym == SDLK_ESCAPE)
		        {
		            SDL_SetRelativeMouseMode(SDL_FALSE);
		            SDL_ShowCursor(SDL_TRUE);
		        }
		        break;
		}
		}*/
		
		// calculate delta time
		time_prev = time_now;
		time_now = INPUT_time_now;
		float time_delta = float(time_now - time_prev);
		
		// get key states
		//auto keys = SDL_GetKeyboardState(nullptr);
		bool up     = key[KEY_W];
		bool down   = key[KEY_S];
		bool left   = key[KEY_A];
		bool right  = key[KEY_D];
	
		// move camera
		float advance = (up ? 1.0f : 0.0f) - (down ? 1.0f : 0.0f);
		float strafe = (right ? 1.0f : 0.0f) - (left ? 1.0f : 0.0f);
		
		float move_speed = 2.2f;
		float move_factor = time_delta * move_speed;
		
		camera.Move(move_factor * advance, move_factor * strafe, 0.0f);
		
		// clear target
		target.ClearSurface(VIDEO_Color{ 0, 0, 0, 255 });
		target.ClearDepth();
		
		// draw floor with a texture
		renderer3d.SetSampler(goober);
		renderer3d.Blit3DModel(target, camera, screen, floor_model);
		
		// draw crate
		renderer3d.SetSampler(crate);
		renderer3d.Blit3DModel(target, camera, screen, crate_model);
		
		// draw spike and colored triangle
		renderer3d.SetSampler(nullptr);
		renderer3d.Blit3DModel(target, camera, screen, triangle_model);
		
		auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 2.0f));
		renderer3d.Blit3DModel(target, camera, screen, spike_model, transform);
		
		// present our finished drawing to the window
		VIDEO_UpdateAndPresent();
		//SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch);
		//SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		//SDL_RenderPresent(renderer);
	}
	
	// quit sdl
	//VIDEO_quit();
	
	// nothing ever goes wrong :D
	return 0;
}