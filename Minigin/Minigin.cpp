#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <steam_api.h>

#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeSingleton.h"

#include <chrono>
#include <thread>

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();

	SteamAPI_Shutdown();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();

	// GAME LOOP
	//-----------
	bool do_continue = true;
	auto last_time = std::chrono::high_resolution_clock::now();;
	float lag = 0.0f;
	const float fixed_time_step = 0.02f;
	const int ms_per_frame = 16;
	
	while (do_continue)
	{
		const auto current_time = std::chrono::high_resolution_clock::now();;
		const float delta_time = std::chrono::duration<float>(current_time - last_time).count()	;
		last_time = current_time;
		lag += delta_time;

		//1. PROCESS INPUT
		time.DeltaTime = delta_time;
		SteamAPI_RunCallbacks();
		do_continue = input.ProcessInput();

		//2. UPDATE GAME
		while (lag >= fixed_time_step)
		{
			sceneManager.FixedUpdate(fixed_time_step);
			lag -= fixed_time_step;
		}
		sceneManager.Update(delta_time);
		//3. RENDER
		renderer.Render();

		//4. Wait until time for next frame.
		const auto sleep_time = current_time + std::chrono:: milliseconds(ms_per_frame) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleep_time);
	}
}
