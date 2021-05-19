#pragma once
class Settings
{
public:
	Settings(int* master_volume, bool* sfx, bool* music);
	~Settings();

	int* master_volume_;
	bool* b_sfx_;
	bool* b_music_;
	
};

