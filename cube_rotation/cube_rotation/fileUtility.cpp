#include "fileUtility.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

std::string getRessourceFile(const std::string& filename) {
	std::string ressourceDir("");
#if defined(_RESSOURCE_DIR_)
#if defined(_WIN32) || defined(_WIN64)
	std::wstring ws(_RESSOURCE_DIR_);
	ressourceDir = std::string(ws.begin(), ws.end());
#endif // defined(_WIN32) || defined(_WIN64)
#if defined(__linux__)
	ressourceDir = _RESSOURCE_DIR_;
#endif // defined(__linux__)
#endif // defined(_RESSOURCE_DIR_)
	if (ressourceDir != "") {
		for (const auto & path : fs::directory_iterator(ressourceDir)) {
			std::string currentFilename = path.path().filename().string();
			if (filename == currentFilename) {
				return path.path().string();
			}
		}
	}
	return ressourceDir;
}
