#pragma once
class Settings
{
public:
	Settings(int* master_volume, bool* sfx, bool* music, int* difficulty);
	~Settings();

	int* difficulty_;
	int* master_volume_;
	bool* b_sfx_;
	bool* b_music_;
	
};

