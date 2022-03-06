#include "level.h"

Level::Level() {
	bricks = new GameObject[MAP_SIZE];
	image = NULL;
}

Level::~Level() {
	delete[] bricks;
}

void Level::init(Texture2D* default_texture) {
	image = default_texture;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			bricks[j + i * 20].pos.x = -1.0f + i / 10.0f + 1 / 20.0f;
			bricks[j + i * 20].pos.y = -1.0f + j / 10.0f + 1 / 20.0f;
			bricks[j + i * 20].size.x = 1 / 20.0f;
			bricks[j + i * 20].size.y = 1 / 20.0f;
			bricks[j + i * 20].image = NULL;

			bricks[j + i * 20].cols = 2;
			bricks[j + i * 20].rows = 2;
		}
	}

	for (int i = 0; i < 20 * 20; i++) {
		bricks[i].frame = i % 3;
		if (i%3) bricks[i].solid = true;
	}
}

void Level::loadLevel(const char* const file) {
	std::string vs = Utility::getFileData(file);
	const char* cvs = vs.c_str();
}