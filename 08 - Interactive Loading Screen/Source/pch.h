#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef NOHELP
#define NOHELP
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <Windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Utility/Debug.h"

namespace IET
{
	typedef std::optional<sf::Event> Event;
	typedef std::string String;
	typedef std::mutex Mutex;
}