#include "../Vars.h"

class CESP
{
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