#pragma once

#include <android/asset_manager.h>
#include <util/string.h>

class FileUtils {
public:
	static AAssetManager* assetManager;

	static void ReadFile(const char* const path, void** data, unsigned int* size);
	static String ReadTextFile(const char* const path);

	static void PrintFiles(const char* const path);
};
