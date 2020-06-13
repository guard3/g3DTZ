#include "Extract.h"
#include "Train.h"
#include "Ferry.h"
#include "Utils.h"
#include "FileSystem.h"
#include <fstream>

bool ExtractPathData()
{
	if (!CFileSystem::CreateAndChangeFolder("paths"))
	{
		ErrorBoxCannotCreateFolder("paths");
		return false;
	}

	std::ofstream f;
	int i;
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
		f	<< std::endl << CFerry::GetNode(i)->GetPosition().x
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
			f	<< std::endl << nodes[i].GetPosition().x
				<< '\t'      << nodes[i].GetPosition().y
				<< '\t'      << nodes[i].GetPosition().z;
		}
		f.close();
		return true;
	};

#define CHECK(a) if (!(a)) return false;
	/* Extract train data */
	CHECK(extractTrain("tracks.dat",  CTrain::GetTrackNode(0),   CTrain::GetNumTrackNodes()  ));
	CHECK(extractTrain("tracks2.dat", CTrain::GetTrackNode_S(0), CTrain::GetNumTrackNodes_S()));

#endif

	CFileSystem::ResetFolder();

	return true;
}