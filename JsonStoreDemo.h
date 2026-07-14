#pragma once

#include <string>

// data.json을 읽고, count 값을 하나 늘려서 다시 저장하는 PoC 데모.
// 실행할 때마다 count가 1씩 증가하는 것으로 read -> 수정 -> write를 확인한다.
void runJsonStoreDemo(const std::string& path);
