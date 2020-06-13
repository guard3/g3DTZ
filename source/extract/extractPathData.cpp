#include "Extract.h"
#include "Train.h"
#include "Ferry.h"
#include "Plane.h"
#include "Utils.h"
#include "FileSystem.h"
#include <fstream>

bool ExtractPathData()
{
#ifdef LCS
	if (!CFileSystem::CreateAndChangeFolder("paths"))
	{
		ErrorBoxCannotCreateFolder("paths");
		return false;
	}
#endif

	/* Open flight.dat */
	int i;
	std::ofstream f("flight.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("flight.dat");
		return false;
	}
	f << CPlane::GetNumPlaneNodes();

	/* Print flight.dat lines */
	for (i = 0; i < CPlane::GetNumPlaneNodes(); ++i)
	{
		f	<< std::endl << PrecisionAny(CPlane::GetPlaneNode(i)->GetPosition().x)
			<< '\t'      << CPlane::GetPlaneNode(i)->GetPosition().y
			<< '\t'      << PrecisionAny(CPlane::GetPlaneNode(i)->GetPosition().z);
	}
	f.close();
	
#ifdef LCS
	/* Open ferry1.dat */
	f.open("ferry1.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("ferry1.dat");
		return false;
	}
	f << CFerry::GetNumNodes();

	/* Print ferry1.dat lines*/
	for (i = 0; i < CFerry::GetNumNodes(); ++i)
	{
		f	<< std::endl << PrecisionAny(CFerry::GetNode(i)->GetPosition().x)
			<< '\t'      << CFerry::GetNode(i)->GetPosition().y
			<< '\t'      << CFerry::GetNode(i)->GetPosition().z;
	}
	f.close();

	/* A lambda that extracts train data */
	auto extractTrain = [&i, &f](const char* filename, CTrainNode* nodes, int num) {
		/* Open file */
		f.open(filename);
		if (!f)
		{
			ErrorBoxCannotCreateFile(filename);
			return false;
		}
		f << num;

		/* Print train lines */
		for (i = 0; i < num; ++i)
		{
			f	<< std::endl << PrecisionAny(nodes[i].GetPosition().x)
				<< '\t'      << PrecisionAny(nodes[i].GetPosition().y)
				<< '\t'      << nodes[i].GetPosition().z;
		}
		f.close();
		return true;
	};

	/* Extract train data */
#define CHECK(a) if (!(a)) return false;
	CHECK(extractTrain("tracks.dat",  CTrain::GetTrackNode(0),   CTrain::GetNumTrackNodes()  ));
	CHECK(extractTrain("tracks2.dat", CTrain::GetTrackNode_S(0), CTrain::GetNumTrackNodes_S()));
	CFileSystem::ResetFolder();
#endif

	return true;
}