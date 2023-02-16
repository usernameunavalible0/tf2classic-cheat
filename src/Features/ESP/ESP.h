#include "../Vars.h"

class CESP
{
private:
	std::wstring ConvertUtf8ToWide(const std::string& str);

private:
	bool IsAmmo(const int modelindex);
	bool IsHealth(const int modelindex);
	bool ShouldRun();
	bool GetDrawBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h);
	Color GetDrawColor(C_BaseEntity* pLocal, C_BaseEntity* pEntity);

public:
	std::vector<int> m_vecHealth = { };
	std::vector<int> m_vecAmmo = { };
	void Paint();
};

namespace F { inline CESP ESP; }