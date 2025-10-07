#pragma once 

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <map>
#include <string>
#include "social_network_types.h"


using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

static int64_t current_timestamp = -1;
static int counter = 0;

class UniqueIdService {
    public:
        UniqueIdService(std::mutex *, const std::string &);
        static int GetCounter(int64_t timestamp);
        int64_t ComposeUniqueId(int64_t, PostType::type, const std::map<std::string, std::string> &);
        std::string GetMachineId(std::string &netif);
        u_int16_t HashMacAddressPid(const std::string &mac);
    private:
        std::mutex *_thread_lock;
        std::string _machine_id;
};