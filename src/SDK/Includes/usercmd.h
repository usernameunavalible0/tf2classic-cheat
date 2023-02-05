#pragma once
#include "c_baseentity.h"

class CUserCmd
{
public:
	virtual ~CUserCmd() { };

	int command_number = 0;
	int tick_count = 0;
	Vector viewangles = {};
	float forwardmove = 0.0f;
	float sidemove = 0.0f;
	float upmove = 0.0f;
	int buttons = 0;
	unsigned char impulse = 0;
	int weaponselect = 0;
	int weaponsubtype = 0;
	int random_seed = 0;
	short mousedx = 0;
	short mousedy = 0;
	bool hasbeenpredicted = false;
};