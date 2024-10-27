#include "AnimManager.h"

/*
 * The global instance of CAnimManager.
 * Initialized when LoadResourceImage() is called from main
 */
CAnimManager* CAnimManager::mspInst;

#ifdef LCS
/* 84 in total; not defining everything because only names are necessary for extraction */
const CAnimManager::AnimAssocDefinition CAnimManager::ms_aAnimAssocDefinitions[84]{
	{ "man",          "ped",       1, 169, nullptr, nullptr },
	{ "van",          "van",       1, 8,   nullptr, nullptr },
	{ "coach",        "coach",     1, 5,   nullptr, nullptr },
	{ "bikes",        "bikes",     1, 18,  nullptr, nullptr },
	{ "bikev",        "bikev",     1, 18,  nullptr, nullptr },
	{ "bikeh",        "bikeh",     1, 18,  nullptr, nullptr },
	{ "biked",        "biked",     1, 18,  nullptr, nullptr },
	{ "unarmed",      "ped",       1, 3,   nullptr, nullptr },
	{ "screwdrv",     "ped",       1, 5,   nullptr, nullptr },
	{ "knife",        "knife",     1, 5,   nullptr, nullptr },
	{ "baseball",     "baseball",  1, 5,   nullptr, nullptr },
	{ "golfclub",     "baseball",  1, 5,   nullptr, nullptr },
	{ "chainsaw",     "chainsaw",  1, 3,   nullptr, nullptr },
	{ "python",       "python",    1, 4,   nullptr, nullptr },
	{ "colt45",       "colt45",    1, 5,   nullptr, nullptr },
	{ "shotgun",      "shotgun",   1, 2,   nullptr, nullptr },
	{ "buddy",        "buddy",     1, 3,   nullptr, nullptr },
	{ "tec",          "tec",       1, 4,   nullptr, nullptr },
	{ "uzi",          "uzi",       1, 4,   nullptr, nullptr },
	{ "rifle",        "rifle",     1, 4,   nullptr, nullptr },
	{ "m60",          "m60",       1, 3,   nullptr, nullptr },
	{ "sniper",       "sniper",    1, 3,   nullptr, nullptr },
	{ "grenade",      "grenade",   1, 3,   nullptr, nullptr },
	{ "flame",        "flame",     1, 1,   nullptr, nullptr },
	{ "rocketla",     "rocketla",  1, 3,   nullptr, nullptr },
	{ "medic",        "medic",     1, 1,   nullptr, nullptr },
	{ "sunbathe",     "sunbathe",  1, 1,   nullptr, nullptr },
	{ "playidles",    "playidles", 1, 4,   nullptr, nullptr },
	{ "riot",         "riot",      1, 7,   nullptr, nullptr },
	{ "strip",        "strip",     1, 7,   nullptr, nullptr },
	{ "lance",        "lance",     1, 1,   nullptr, nullptr },
	{ "player",       "ped",       1, 5,   nullptr, nullptr },
	{ "playerrocket", "ped",       1, 5,   nullptr, nullptr },
	{ "player1armed", "ped",       1, 5,   nullptr, nullptr },
	{ "player2armed", "ped",       1, 5,   nullptr, nullptr },
	{ "playerBBBat",  "ped",       1, 5,   nullptr, nullptr },
	{ "aicsaw2",      "ped",       1, 5,   nullptr, nullptr },
	{ "playercsaw",   "ped",       1, 5,   nullptr, nullptr },
	{ "shuffle",      "ped",       1, 4,   nullptr, nullptr },
	{ "oldman",       "ped",       1, 4,   nullptr, nullptr },
	{ "gang1",        "ped",       1, 4,   nullptr, nullptr },
	{ "gang2",        "ped",       1, 4,   nullptr, nullptr },
	{ "fatman",       "ped",       1, 4,   nullptr, nullptr },
	{ "oldfatman",    "ped",       1, 4,   nullptr, nullptr },
	{ "jogger",       "ped",       1, 4,   nullptr, nullptr },
	{ "woman",        "ped",       1, 4,   nullptr, nullptr },
	{ "shopping",     "ped",       1, 4,   nullptr, nullptr },
	{ "busywoman",    "ped",       1, 4,   nullptr, nullptr },
	{ "sexywoman",    "ped",       1, 4,   nullptr, nullptr },
	{ "fatwoman",     "ped",       1, 4,   nullptr, nullptr },
	{ "oldwoman",     "ped",       1, 4,   nullptr, nullptr },
	{ "jogwoman",     "ped",       1, 4,   nullptr, nullptr },
	{ "panicchunky",  "ped",       1, 4,   nullptr, nullptr },
	{ "skate",        "skate",     1, 4,   nullptr, nullptr },
	{ "playerback",   "ped",       1, 5,   nullptr, nullptr },
	{ "playerleft",   "ped",       1, 5,   nullptr, nullptr },
	{ "playerright",  "ped",       1, 5,   nullptr, nullptr },
	{ "rocketback",   "ped",       1, 5,   nullptr, nullptr },
	{ "rocketleft",   "ped",       1, 5,   nullptr, nullptr },
	{ "rocketright",  "ped",       1, 5,   nullptr, nullptr },
	{ "MPNote",       "MPNote",    1, 2,   nullptr, nullptr },
	{ "CS_MISC",      "CS_MISC",   1, 8,   nullptr, nullptr },
	{ "DONH2",        "DONH2",     1, 1,   nullptr, nullptr },
	{ "DONH3",        "DONH3",     1, 1,   nullptr, nullptr },
	{ "JDT2",         "JDT2",      1, 2,   nullptr, nullptr },
	{ "JDT4",         "JDT4",      1, 1,   nullptr, nullptr },
	{ "JDT5",         "JDT5",      1, 2,   nullptr, nullptr },
	{ "JDT6",         "JDT6",      1, 2,   nullptr, nullptr },
	{ "MAR1",         "MAR1",      1, 1,   nullptr, nullptr },
	{ "MAR2",         "MAR2",      1, 4,   nullptr, nullptr },
	{ "MAR3",         "MAR3",      1, 3,   nullptr, nullptr },
	{ "SAL1",         "SAL1",      1, 1,   nullptr, nullptr },
	{ "SAL2",         "SAL2",      1, 2,   nullptr, nullptr },
	{ "SAL3",         "SAL3",      1, 3,   nullptr, nullptr },
	{ "SAL4",         "SAL4",      1, 2,   nullptr, nullptr },
	{ "SAL6",         "SAL6",      1, 2,   nullptr, nullptr },
	{ "SAL7",         "SAL7",      1, 1,   nullptr, nullptr },
	{ "VIC2",         "VIC2",      1, 1,   nullptr, nullptr },
	{ "VIC3",         "VIC3",      1, 2,   nullptr, nullptr },
	{ "VIC4",         "VIC4",      1, 3,   nullptr, nullptr },
	{ "VIC6",         "VIC6",      1, 1,   nullptr, nullptr },
	{ "TOURIST",      "TOURIST",   1, 3,   nullptr, nullptr },
	{ "MAC2",         "MAC2",      1, 1,   nullptr, nullptr },
	{ "VIC7",         "VIC7",      1, 1,   nullptr, nullptr },
};
#endif

const char* CAnimBlendAssocGroup::GetName()
{
#ifdef LCS
	/*
	 * Anim assoc group names aren't needed in the game, so LCS has them discarded.
	 * For that reason, we need to have a table with names, figured out from LCS mobile.
	 */
	return CAnimManager::ms_aAnimAssocDefinitions[m_grpId].pName;
#else
	/*
	 * VCS on the other hand seems to have some temporary tables(?) still loaded in memory
	 * So we can salvage names and other stuff from there
	 */
	return CAnimManager::mspInst->m_aAnimAssocDefinitions[m_grpId].pName;
#endif
}