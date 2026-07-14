#pragma once

#include <string>

// Reads a JSON file, increments its "count" field, writes it back.
// Running this repeatedly bumps count by 1 each time, demonstrating
// read -> modify -> write through JsonStore.
void runJsonStoreDemo(const std::string& path);
