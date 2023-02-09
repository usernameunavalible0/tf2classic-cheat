#pragma once
#include "../Vars.h"

class CMisc
{
public:
	void Bunnyhop(C_BaseEntity* pLocal, CUserCmd* cmd);
};

namespace F { inline CMisc Misc; }