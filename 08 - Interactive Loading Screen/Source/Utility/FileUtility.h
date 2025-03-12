#pragma once
class FileUtility
{
public:
	static std::filesystem::path getFileFromSource(const std::filesystem::path& fileName)
	{
		return SOURCE_PATH / fileName;
	}
	static std::filesystem::path getFileFromAssets(const std::filesystem::path& fileName)
	{
		return getFileFromSource("Media\\") / fileName;
	}
	static std::filesystem::path getFileFromTextures(const std::filesystem::path& fileName)
	{
		return getFileFromAssets("Textures\\") / fileName;
	}
private:
	static inline const std::filesystem::path SOURCE_PATH = std::filesystem::current_path().append("Source\\");
};

