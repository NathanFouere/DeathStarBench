#pragma once
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <net/if.h>
#include <unistd.h>
#include <cstring>

#define CUSTOM_EPOCH 1514764800000

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

static int64_t current_timestamp = -1;
static int counter = 0;

static int GetCounter(int64_t timestamp) {
  if (current_timestamp > timestamp) {
    std::cout << "Timestamps are not incremental." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (current_timestamp == timestamp) {
    return counter++;
  } else {
    current_timestamp = timestamp;
    counter = 0;
    return counter++;
  }
}

struct PostType {
  enum type {
    POST = 0,
    REPOST = 1,
    REPLY = 2,
    DM = 3
  };
};

class UniqueIdHandler {
    public:
        UniqueIdHandler(
            std::mutex *thread_lock,
            const std::string &machine_id
        );
        int64_t ComposeUniqueId(
            int64_t req_id,
            PostType::type post_type,
            const std::map<std::string, std::string> &carrier
        );
        uint16_t HashMacAddressPid(const std::string &mac);
        std::string GetMachineId(std::string &netif);
    private:
        std::mutex *_thread_lock;
        std::string _machine_id;
};
