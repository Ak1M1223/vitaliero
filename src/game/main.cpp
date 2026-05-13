// // #ifndef UUID_DC1D9513CDD34960AB8A648004DA149D
// // #define UUID_DC1D9513CDD34960AB8A648004DA149D
// #include <psp2/kernel/processmgr.h>
// #include <SDL2/SDL.h>
#include <vitasdk.h>

#include "gfx.hpp"
#include "sfx.hpp"
#include "sys.hpp"
#include "game.hpp"
#include "viewport.hpp"
#include "worm.hpp"
#include "reader.hpp"
#include "filesystem.hpp"
#include "text.hpp"
#include "keys.hpp"
#include "constants.hpp"
#include "math.hpp"
#include "console.hpp"
#include <gvl/support/platform.hpp>

// #include <ctime>
// #include <exception>
// #include <gvl/math/cmwc.hpp>

// #if __APPLE__
// #define gameEntry SDL_main
// #endif

// void benchAll();

// int gameEntry(int argc, char* argv[]){
// 	sceClibPrintf("Liero starting...\n");
// }
// // try
// // {
// // 	sceClibPrintf("Liero starting...\n");
// // 	// TODO: Better PRNG seeding
// // 	gfx.rand.seed(Uint32(std::time(0)));

// // #if 0
// // 	benchAll();
// // 	return 0;
// // #elif 0
// // 	std::string const& path = "D:\\cpp\\liero\\tc";
// // 	FsNode node(path);

// // 	for (DirectoryListing dir = node.iter(); dir; ++dir)
// // 	{
// // 		auto d = *dir;

// // 		try
// // 		{
// // 			auto zipNode = node / d;

// // 			bool found = false;

// // 			for (DirectoryListing zipDir = zipNode.iter(); zipDir; ++zipDir)
// // 			{
// // 				auto e = *zipDir;
// // 				auto upper = e;
// // 				toUpperCase(upper);

// // 				if (upper.find(".EXE") != std::string::npos && upper != "LEVEDIT.EXE")
// // 				{
// // 					found = true;
// // 					Common common(zipNode, e);

// // 					printf("N: %s\n", common.guessName().c_str());
// // 					//printf("N: %s ||| %s\n", common.S[SCopyright2].c_str(), common.S[SCopyright].c_str() + 4);
// // 					break;
// // 				}
// // 			}

// // 			if (!found)
// // 				printf("** No exe found for %s\n", d.c_str());
// // 		}
// // 		catch (std::runtime_error& e)
// // 		{
// // 			//printf("Failed to load: %s\n", d.c_str());
// // 			//printf("%s\n", e.what());
// // 		}
// // 	}

// // 	return 0;
// // #endif

// // 	bool tcSet = false;

// // 	std::string tcName;
// // 	std::string configPath; // Default to current dir

// // 	for(int i = 1; i < argc; ++i)
// // 	{
// // 		if(argv[i][0] == '-')
// // 		{
// // 			switch(argv[i][1])
// // 			{
// // 			case '-':
// // 				if (std::strcmp(argv[i] + 2, "config-root") == 0 && i + 1 < argc)
// // 				{
// // 					++i;
// // 					configPath = argv[i];
// // 				}
// // 				break;
// // 			}
// // 		}
// // 		else
// // 		{
// // 			tcName = argv[i];
// // 			tcSet = true;
// // 		}
// // 	}

// // 	SDL_Init(SDL_INIT_VIDEO); //| SDL_INIT_GAMECONTROLLER);

// // 	initKeys();

// // 	precomputeTables();

// // 	gfx.loadMenus();

// // 	gfx.init();
// // 	gfx.setConfigPath(configPath);

// // 	FsNode configNode(gfx.getConfigNode());

// // 	if (!gfx.loadSettings(configNode / "liero.cfg"))
// // 	{
// // 		if (!gfx.loadSettingsLegacy(configNode / "LIERO.DAT"))
// // 		{
// // 			gfx.settings.reset(new Settings);
// // 			gfx.saveSettings(configNode / "liero.cfg");
// // 		}
// // 	}

// // 	if (tcSet)
// // 		gfx.settings->tc = tcName;

// // 	// TC loading
// // 	FsNode lieroRoot(configNode / "TC" / gfx.settings->tc);
// // 	gvl::shared_ptr<Common> common(new Common());
// // 	common->load(std::move(lieroRoot));
// // 	gfx.common = common;
// // 	gfx.playRenderer.loadPalette(*common); // This gets the palette from common

// // 	gfx.setVideoMode();
// // 	sfx.init();

// // 	gfx.mainLoop();

// // 	gfx.settings->save(configNode / "liero.cfg", gfx.rand);

// // 	sfx.deinit();
// // 	SDL_Quit();

// // 	//gvl::present_profile(std::cout);

// // 	return 0;
// // }
// // catch(std::exception&)
// // {
// // 	SDL_Quit();
// // 	throw;
// // }

// // #endif // UUID_DC1D9513CDD34960AB8A648004DA149D

#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>

//Screen dimension constants
//enum {
//  SCREEN_WIDTH  = 960,
//  SCREEN_HEIGHT = 544
//};

//SDL_Window    * gWindow   = NULL;
//SDL_Renderer  * gRenderer = NULL;

// SDL_Rect fillRect = { SCREEN_WIDTH  / 4,
// 		      SCREEN_HEIGHT / 4,
// 		      SCREEN_WIDTH  / 2,
// 		      SCREEN_HEIGHT / 2
// };



int main(int argc, char* argv[])
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return -1;

	//if ((gWindow = SDL_CreateWindow( "RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	//	return -1;

	//if ((gRenderer = SDL_CreateRenderer( gWindow, -1, 0)) == NULL)
	//	return -1;
	sceClibPrintf("Liero starting...\n");
	SDL_Delay(10);

//   SDL_SetRenderDrawColor( gRenderer, 255,0,0,255);
//   SDL_RenderFillRect( gRenderer, &fillRect );
//   SDL_RenderPresent( gRenderer );
//   SDL_Delay(4000);
//   SDL_DestroyRenderer( gRenderer );
//   SDL_DestroyWindow( gWindow );

	gfx.rand.seed(time(NULL));
	sceClibPrintf("Random seed initialized...\n");
	printf("SDL initialized...\n");
	initKeys();
	sceClibPrintf("Keys initialized...\n");
	precomputeTables();
	sceClibPrintf("Math tables precomputed...\n");
	gfx.loadMenus();
	sceClibPrintf("Menus loaded...\n");
	gfx.init();
	sceClibPrintf("Graphics initialized...\n");
	gfx.setConfigPath("ux0:data/openliero/");
	sceClibPrintf("Configuration path set...\n");
	FsNode configNode(gfx.getConfigNode());
	bool tcSet = false;
	std::string tcName;
	if (!gfx.loadSettings(configNode / "liero.cfg"))
	{
		if (!gfx.loadSettingsLegacy(configNode / "LIERO.DAT"))
		{
			gfx.settings.reset(new Settings);
			gfx.saveSettings(configNode / "liero.cfg");
		}
	}

	if (tcSet)
		gfx.settings->tc = tcName;

	// TC loading
	FsNode lieroRoot(configNode / "TC" / gfx.settings->tc);
	sceClibPrintf("Found DataFiles...\n");
	gvl::shared_ptr<Common> common(new Common());
	common->load(std::move(lieroRoot));
	gfx.common = common;
	gfx.playRenderer.loadPalette(*common); // This gets the palette from common
	sceClibPrintf("Palette initialized...\n");
	gfx.setVideoMode();
	sceClibPrintf("Video mode set...\n");
	sfx.init();
	sceClibPrintf("SFX initialized...\n");
	sceClibPrintf("Main loop starting...\n");
	gfx.mainLoop();
	sceClibPrintf("Main loop stop...\n");
	gfx.settings->save(configNode / "liero.cfg", gfx.rand);

	sfx.deinit();
	//SDL_DestroyRenderer( gRenderer );
	//SDL_DestroyWindow( gWindow );
	//gWindow = NULL;
	//gRenderer = NULL;

	SDL_Quit();
	return 0;
}
//ux0:/data/