#include "PedType.h"

static const char* const flagNames[]{
	"PLAYER1",
	"PLAYER2",
	"PLAYER3",
	"PLAYER4",
	"CIVMALE",
	"CIVFEMALE",
	"COP",
	"GANG1",
	"GANG2",
	"GANG3",
	"GANG4",
	"GANG5",
	"GANG6",
	"GANG7",
	"GANG8",
	"GANG9",
	"EMERGENCY",
	"PROSTITUTE",
	"CRIMINAL",
	"SPECIAL",
	"GUN",
	"COP_CAR",
	"FAST_CAR",
	"EXPLOSION",
	"FIREMAN",
	"DEADPEDS"
};

const char* CPedType::GetFlagName()
{
	int i = 0;
	for (uint32 f = m_nFlag; f != 1; f >>= 1) ++i;
	return flagNames[i];
}

const char* CPedType::GetFlagName(int index)
{
	return flagNames[index];
}