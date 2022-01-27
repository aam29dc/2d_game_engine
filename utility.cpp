#include "utility.h"

std::string Utility::getFileData(const char* const loc) {
	std::ifstream file(loc);
	std::string contents;

	if (file.is_open()) {
		while (file) {
			contents += file.get();
		}
	}
	else {
		std::cout << "ERROR: Utility - failed to open: " << loc << std::endl;
	}
	file.close();

	contents[contents.size() - 1] = '\0';

	return contents;
}