#pragma once

// StandardTemplateLibrary Header
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <atomic>
#include <type_traits>

#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>

//Windows Specific Header
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

//Custom Headers
#include "Logging/log.h"
#include "Logging/Timer.h"
#include "Structures/UnrealDataTypesEmulator.h"