#include "renderer.hpp"
#include "blit.hpp"
#include "../common.hpp"
#include <vitasdk.h>

void Renderer::init(int x, int y)
{
	this->setRenderResolution(x, y);
}

void Renderer::setRenderResolution(int x, int y)
{
	renderResX = x;
	renderResY = y;
	sceClibPrintf("Allocating bitmap for render resolution %d x %d...\n", renderResX, renderResY);
	bmp.alloc(renderResX, renderResY);
}

void Renderer::loadPalette(Common const& common)
{
	origpal = common.exepal;
	pal = origpal;
}

void Renderer::clear()
{
	fill(bmp, 0);
}
