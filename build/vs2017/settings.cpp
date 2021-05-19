#include "settings.h"

Settings::Settings(int* master_volume, bool* sfx, bool* music) :
	master_volume_(master_volume),
	b_sfx_(sfx),
	b_music_(music)
{
}

Settings::~Settings()
{
}
