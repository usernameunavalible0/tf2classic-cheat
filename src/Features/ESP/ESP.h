#include "../Vars.h"

class CESP
{
public:
	bool bActive = true;
	bool bOutline = false;

	bool bPlayers = true;
	int nNoTeammatePlayers = 0; //0 off 1 all 2 keep friends
	bool bPlayerName = true;
	bool bPlayerClass = false;
	bool bPlayerHealth = false;
	bool bPlayerCond = false;
	bool bPlayerHealthBar = true;
	int nPlayerBox = 1; //0 off 1 simple 2 corners

	bool bDebug = false;

private:
	std::wstring ConvertUtf8ToWide(const std::string& str);

private:
	bool ShouldRun();
	bool GetDrawBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h);
	Color GetDrawColor(C_BaseEntity* pLocal, C_BaseEntity* pEntity);

public:
	void Paint();
};

namespace F { inline CESP ESP; }