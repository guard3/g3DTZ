#include <filesystem>
#include <fstream>
#include <iostream>
#include "Extract.h"
#include "FileSystem.h"
#include "ResourceImage.h"
#include "Utils.h"

namespace fs = std::filesystem;

void DealWithAnimFile(fs::path, const base::sChunkHeader& header, std::ifstream& inputStream);

int
wmain(int argc, const wchar** argv) {
	/* Check that only one argument is specified */
	if (argc != 2) {
		ErrorBox("Invalid number of arguments.\nSimply drag n' drop a GAME.DTZ/GAME.DAT or .ANIM file to this executable.");
		return EXIT_FAILURE;
	}

	try {
		/* Load the header of the input file to determine the type */
		fs::path argPath = fs::canonical(argv[1]);
		std::ifstream inputStream(argPath, std::ios::binary);
		base::sChunkHeader header{};
		if (!inputStream.read(reinterpret_cast<char*>(&header), sizeof(header))) {
			ErrorBox("Can't open or read from input file.");
			return EXIT_SUCCESS;
		}
		if (header.ident == 'anim') {
			/* The input is an anim file */
			DealWithAnimFile(std::move(argPath), header, inputStream);
			return EXIT_SUCCESS;
		}
		/* Otherwise, input is a GAME.DTZ or GAME.DAT */
		/* Initialize filesystem */
		if (!CFileSystem::Initialize(argv[1]))
			return EXIT_FAILURE;

		/* Load GAME.DTZ */
		LoadResourceImage(argPath, header, inputStream);

		std::cout << "Extracting...\n";
#define CHECK(a) if (!(a)) return EXIT_FAILURE;
		CHECK(ExtractAnimations());
		CHECK(ExtractIPLs());
		CHECK(ExtractModelInfoAndStuff());
		CHECK(ExtractObjectData());
		CHECK(ExtractFightMoves());
		CHECK(ExtractPedType());
		CHECK(ExtractPedStats());
		CHECK(ExtractPedGroups());
		CHECK(ExtractWeaponInfo());
		CHECK(ExtractTimeCycle());
		CHECK(ExtractSurfaceTable());
		CHECK(ExtractDIRs());
		CHECK(ExtractParticle());
		CHECK(ExtractWaterLevel());
		CHECK(ExtractZones());
		CHECK(ExtractPathData());
		std::cout << "All done!\n";

		return EXIT_SUCCESS;
	}
	catch (const std::bad_alloc&) {
		ErrorBox("Out of memory.");
		return EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		ErrorBox("%s", e.what());
		return EXIT_FAILURE;
	}
	catch (...) {
		ErrorBox("An error occurred.");
		return EXIT_FAILURE;
	}
}

void
DealWithAnimFile(fs::path inputPath, const base::sChunkHeader& header, std::ifstream& inputStream) {
	/* Override the current working directory because I don't want to deal with CFileSystem crap right now */
	std::cout << inputPath << '\n';
	fs::current_path(fs::canonical(inputPath).parent_path());
	/* Load the rest of the file into a buffer*/
	std::vector<char> buff(header.fileEnd);
	std::memcpy(buff.data(), &header, sizeof(header));
	if (!inputStream.read(buff.data() + sizeof(header), buff.size() - sizeof(header)))
		throw std::runtime_error("Invalid file.");
	/* Fixup chunk */
	CAnimBlendTree** pTrees = reinterpret_cast<CAnimBlendTree**>(base::cRelocatableChunk::Load(buff.data()));
	/* Now here's the thing...
	 * For proper extraction, GAME.DAT must be loaded because the anim manager has all info about the game's anim blocks, even
	 * the ones that are not loaded. The .anim files themselves don't have that info. It seems like a stretch to request that
	 * the user also supply that. There is a workaround though: test each anim tree pointer until it's invalid, that is, its
	 * value is not in range of the loaded chunk, then we have successfully determined the number of animations in the file! */
	std::size_t numTrees = 0;
	for (; reinterpret_cast<char*>(pTrees[numTrees]) > buff.data() && reinterpret_cast<char*>(pTrees[numTrees]) < buff.data() + buff.size(); ++numTrees);
	if (numTrees == 0)
		throw std::runtime_error("Input file has no animations");
	/* Now we can proceed with the export */
	auto f = [&] {
		std::string filename = inputPath.replace_extension("ifp").filename().string();
		std::FILE* f = std::fopen(filename.c_str(), "wb");
		if (!f)
			throw std::runtime_error(std::format("Cannot open output file {}", filename));
		return std::unique_ptr<std::FILE, int(*)(std::FILE*)>(f, std::fclose);
	}();
	std::cout << "Detected " << numTrees << " animation" << (numTrees == 1 ? "" : "s") << "\nExporting to IFP...\n";
	ExportAnimations(f.get(), inputPath.stem().string(), { pTrees, numTrees });
	std::cout << "All done!\n";
}