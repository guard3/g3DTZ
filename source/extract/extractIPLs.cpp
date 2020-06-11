#include "Extract.h"
#include "Pools.h"
#include "CullZones.h"
#include <fstream>
#include "Win32.h"
#include "Utils.h"
#include "FileSystem.h"

template<typename T>
bool ExtractIPL(CPool<T>* pool)
{	
	/* Get output file name */
	char filename[20]; // Max pool name is 16 chars + 4 for the file extension
	int i;
	{
		const char* poolName = pool->GetName();
		for (i = 0; poolName[i]; ++i)
			filename[i] = poolName[i];
		strcpy(filename + i, ".ipl");
	}

	/* Open output file */
	std::ofstream f(filename);
	if (!f)
	{
		ErrorBoxCannotCreateFile(filename);
		return false;
	}

	/* Write to file */
	f << "# " << G3DTZ_MESSAGE << std::endl << "inst" << std::endl;
	for (i = 0; i < pool->GetSize(); ++i)
	{
		if (auto entity = pool->GetSlot(i))
		{
			f	<< entity->GetModelIndex() << ", "
				<< entity->GetModelName() << ", 0, "
				<< entity->GetTranslation().x << ", "
				<< entity->GetTranslation().y << ", "
				<< entity->GetTranslation().z << ", 1, 1, 1, "
				<< entity->GetRotation().x << ", "
				<< entity->GetRotation().y << ", "
				<< entity->GetRotation().z << ", "
				<< entity->GetRotation().w << std::endl;
		}
	}
	f << "end" << std::endl;
	return true;
}

bool ExtractIPLs()
{
	/* Create folder for IPLs */
	if (!CFileSystem::CreateAndChangeFolder("ipl"))
	{
		ErrorBoxCannotCreateFolder("ipl");
		return false;
	}

	/* Extract normal IPLs */
	if (!ExtractIPL(CPools::GetBuildingPool()))  return false;
	if (!ExtractIPL(CPools::GetTreadablePool())) return false;
	if (!ExtractIPL(CPools::GetDummyPool()))     return false;

	/* Open cull.ipl */
	std::ofstream f("cull.ipl");
	if (!f)
	{
		ErrorBoxCannotCreateFile("cull.ipl");
		return false;
	}
	f << "# " << G3DTZ_MESSAGE << std::endl << "cull" << std::endl;

	/* Print cull.ipl lines */
	for (int i = 0; i < CCullZones::GetNumAttributeZones(); ++i)
	{
		CAttributeZone* attrZone = CCullZones::GetAttributeZone(i);
		f	<< attrZone->GetPositionX()          << ", "
			<< attrZone->GetPositionY()          << ", "
			<< attrZone->GetPositionZ()          << ", "
			<< attrZone->GetLowPointX()  << ".0" << ", "
			<< attrZone->GetLowPointY()  << ".0" << ", "
			<< attrZone->GetLowPointZ()  << ".0" << ", "
			<< attrZone->GetHighPointX() << ".0" << ", "
			<< attrZone->GetHighPointY() << ".0" << ", "
			<< attrZone->GetHighPointZ() << ".0" << ", "
			<< attrZone->GetAttribute()          << ", "
			<< attrZone->GetWantedLevel() << std::endl;
	}
	f << "end" << std::endl;
	f.close();

	/* Reset working directory */
	CFileSystem::ResetFolder();
	return true;
}