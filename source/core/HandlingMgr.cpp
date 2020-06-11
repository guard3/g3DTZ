#include "HandlingMgr.h"
#include <stdio.h>
#include <math.h>

char flags_str[9];

#ifdef LCS
char temp_float[] = "\0\0\0.0";

const char* CTransmission::GetMaxVelocity()
{
	/*
	 * When the game parses the value for fMaxVelocity, this value is devided by 180.0.
	 * For the handling of RCBANDIT, this is kept as is because we love crazy handling for rc toys!
	 * But for other vehicles, there are some constraints depending on the fDragMult, so the resulting value
	 * is further reduced by some multiple of 0.01 and then gets multiplied by 1.2. If the game ever needs to
	 * get the actual value of fMaxVelocity, it multiplies by 180.0 and everything's good, but that value is
	 * now totally different from the value that existed in the HANDLING.CFG file originally and I don't think
	 * it's possible to ever restore it for extraction purposes. But in LCS we can overcome this problem by
	 * using the values from LCS Mobile
	 */
	static const char max_velocities[][4] {
		"160", "160", "230", "120", "150", "165", "170", "170", "110",
		"180", "160", "240", "160", "140", "230", "155", "200", "150",
		"160", "180", "160", "165", "145", "170", "200", "110", "170",
		"200", "130", "80",  "180", "110", "190", "200", "200", "160",
		"160", "160", "160", "78",  "190", "200", "200", "140", "160",
		"200", "140", "140", "160", "200", "160", "165", "165", "140",
		"205", "160", "160", "230", "180", "200", "230", "165", "200",
		"200", "160", "190", "190", "185", "188", "190", "190", "190",
		"190", "190", "190", "200", "200", "200", "200", "75",  "75"
	};

	/* Little hack */
	const char* velocity = max_velocities[reinterpret_cast<CHandlingData*>(reinterpret_cast<uint32*>(this) - 14)->nIdentifier];
	if (velocity[2])
	{
		temp_float[0] = velocity[0];
		temp_float[1] = velocity[1];
		temp_float[2] = velocity[2];
		return temp_float;
	}

	temp_float[1] = velocity[0];
	temp_float[2] = velocity[1];
	return temp_float + 1;
}

const char* const handling_names[]{
		"LANDSTAL", "IDAHO",    "STINGER",  "LINERUN",  "PEREN",    "SENTINEL", "PATRIOT",  "FIRETRUK", "TRASH",
		"STRETCH",  "MANANA",   "INFERNUS", "PONY",     "MULE",     "CHEETAH",  "AMBULAN",  "FBICAR",   "MOONBEAM",
		"ESPERANT", "TAXI",     "KURUMA",   "BOBCAT",   "MRWHOOP",  "BFINJECT", "POLICE",   "ENFORCER", "SECURICA",
		"BANSHEE",  "BUS",      "RHINO",    "BARRACKS", "TRAIN",    "FERRY",    "HELI",     "DODO",     "COACH",
		"CABBIE",   "STALLION", "RUMPO",    "RCBANDIT", "MAFIA",    "AIRTRAIN", "DEADDODO", "FLATBED",  "YANKEE",
		"BLISTA",   "BELLYUP",  "MRWONGS",  "YARDIE",   "YAKUZA",   "DIABLOS",  "COLUMB",   "HOODS",    "PANLANT",
		"BORGNINE", "CAMPVAN",  "BALLOT",   "SPIDER",   "SHELBY",   "PONTIAC",  "ESPRIT",   "MINI",     "HOTROD",
		"SINDACCO", "FORELLI",  "BIKE",     "MOPED",    "DIRTBIKE", "ANGEL",    "DIRTBIK2", "ANGE2",    "FREEWAY",
		"PREDATOR", "SPEEDER",  "REEFER",   "MAVERICK", "COASTMAV", "POLMAV",   "HUNTER",   "RCGOBLIN", "RCCOPTER",
};
const char* CHandlingData::GetHandlingName()   { return handling_names[nIdentifier]; }
const char* CHandlingBoat::GetHandlingName()   { return handling_names[nIdentifier]; }
const char* CHandlingBike::GetHandlingName()   { return handling_names[nIdentifier]; }
const char* CHandlingFlying::GetHandlingName() { return handling_names[nIdentifier]; }

const char* CHandlingData::GetSuspensionHighSpdComDamp()
{
	/* This value is ignored when the HANDLING.CFG file is parsed, so we can just reuse data from LCS Mobile */
	switch (nIdentifier)
	{
	case 36:
		temp_float[2] = '2';
		break;
	case 6:
		temp_float[2] = '4';
		break;
	case 18:
	case 25:
		temp_float[2] = '1';
		break;
	case 1:
	case 10:
	case 13:
	case 20:
	case 21:
	case 23:
	case 27:
	case 46:
	case 47:
	case 50:
	case 53:
	case 58:
	case 60:
		temp_float[2] = '5';
		break;
	default:
		temp_float[2] = '0';
	}
	return temp_float + 2;
}
#else
const char* CHandlingData::GetHandlingFlags()
{
	sprintf(flags_str, "%X", handlingFlags);
	return flags_str;
}
#endif

const char* CHandlingData::GetModelFlags()
{
	sprintf(flags_str, "%X", modelFlags);
	return flags_str;
}

constexpr float PI = 3.14159265358979323846f;
const char* CHandlingBike::GetMaxLean()      { return Precision(asinf(fMaxLean) * 180.0f / PI);    }
const char* CHandlingBike::GetFullAnimLean() { return Precision(fFullAnimLean * 180.0f / PI);      }
const char* CHandlingBike::GetWheelieAng()   { return Precision(asinf(fWheelieAng) * 180.0f / PI); }
const char* CHandlingBike::GetStoppieAng()   { return Precision(asinf(fStoppieAng) * 180.0f / PI); }