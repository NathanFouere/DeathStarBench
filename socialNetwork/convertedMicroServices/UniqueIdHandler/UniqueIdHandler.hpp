#pragma once
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>


using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

static int64_t current_timestamp = -1;
static int counter = 0;

static int GetCounter(int64_t timestamp) {
  if (current_timestamp > timestamp) {
    LOG(fatal) << "Timestamps are not incremental.";
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
        UniqueIdHandler();
        int64_t ComposeUniqueId(
            int64_t req_id, 
            PostType::type post_type,
            const std::map<std::string, std::string> &carrier
        );
    private:
        std::mutex *_thread_lock;
        std::string _machine_id;
};
