#include "AnimManager.h"

/*
 * The global instance of CAnimManager.
 * Initialized when LoadResourceImage() is called from main
 */
CAnimManager* CAnimManager::mspInst;

#ifdef LCS
#include <map>
std::map<int, const char*> mAnimAssocGroupNames {
	{ 0, "man" },
	{ 7, "unarmed" },
	{ 8, "screwdrv" },
	{ 9, "knife" },
	{ 10, "baseball" },
	{ 12, "chainsaw"},
	{ 13, "python" },
	{ 14, "colt45" },
	{ 15, "shotgun"},
	{ 16, "buddy" },
	{ 17, "tec" },
	{ 18, "uzi"},
	{ 19, "rifle"},
	{ 20, "m60"},
	{ 21, "sniper" },
	{ 22, "grenade" },
	{ 23, "flame" },
	{ 24, "rocketla" },
	{ 31, "player" },
	{ 38, "shuffle" },
	{ 39, "oldman" },
	{ 40, "gang1" },
	{ 41, "gang2" },
	{ 42, "fatman" },
	{ 45, "woman" },
	{ 47, "busywoman" },
	{ 48, "sexywoman" },
	{ 49, "fatwoman" },
	{ 50, "oldwoman" }
};
#endif

const char* CAnimBlendAssocGroup::GetName()
{
#ifdef LCS
	/*
	 * Anim assoc group names aren't needed in the game, so LCS has them discarded.
	 * For that reason, we need to have a table with names, figured out from LCS mobile.
	 */
	return mAnimAssocGroupNames[groupId];
#else
	/*
	 * VCS on the other hand seems to have some temporary tables(?) still loaded in memory
	 * So we can salvage names and other stuff from there
	 */
	return CAnimManager::mspInst->assocGroups[groupId].groupname;
#endif
}