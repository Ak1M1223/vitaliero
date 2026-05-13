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

#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>


int main(int argc, char* argv[])
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return -1;
	sceClibPrintf("Liero starting...\n");
	SDL_Delay(10);

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

	SDL_Quit();
	return 0;
}