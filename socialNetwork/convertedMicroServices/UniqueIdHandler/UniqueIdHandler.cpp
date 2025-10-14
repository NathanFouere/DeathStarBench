#include "UniqueIdHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

UniqueIdHandler::UniqueIdHandler(
    std::mutex *thread_lock,
    const std::string &machine_id
) {
    _thread_lock = thread_lock;
    _machine_id = machine_id;
}

int64_t UniqueIdHandler::ComposeUniqueId(
    int64_t req_id,
    PostType::type post_type,
    const std::map<std::string, std::string> &carrier
) {
    _thread_lock->lock();
    int64_t timestamp =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count() -
        CUSTOM_EPOCH;
    int idx = GetCounter(timestamp);
    _thread_lock->unlock();

    std::stringstream sstream;
    sstream << std::hex << timestamp;
    std::string timestamp_hex(sstream.str());

    if (timestamp_hex.size() > 10) {
      timestamp_hex.erase(0, timestamp_hex.size() - 10);
    } else if (timestamp_hex.size() < 10) {
      timestamp_hex = std::string(10 - timestamp_hex.size(), '0') + timestamp_hex;
    }

    // Empty the sstream buffer.
    sstream.clear();
    sstream.str(std::string());

    sstream << std::hex << idx;
    std::string counter_hex(sstream.str());

    if (counter_hex.size() > 3) {
      counter_hex.erase(0, counter_hex.size() - 3);
    } else if (counter_hex.size() < 3) {
      counter_hex = std::string(3 - counter_hex.size(), '0') + counter_hex;
    }
    std::string post_id_str = _machine_id + timestamp_hex + counter_hex;
    int64_t post_id = stoul(post_id_str, nullptr, 16) & 0x7FFFFFFFFFFFFFFF;
    std::cout << "The post_id of the request " << req_id << " is " << post_id << std::endl;

    return post_id;
}

uint16_t HashMacAddressPid(const std::string &mac) {
  uint16_t hash = 0;
  std::string mac_pid = mac + std::to_string(getpid());
  for (unsigned int i = 0; i < mac_pid.size(); i++) {
    hash += (mac[i] << ((i & 1) * 8));
  }
  return hash;
}

int GetMachineId (std::string *mac_hash) {
  std::string mac;
  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP );
  if ( sock < 0 ) {
    std::cout << "Unable to obtain MAC address" << std::endl;
    return -1;
  }

  struct ifconf conf{};
  char ifconfbuf[ 128 * sizeof(struct ifreq)  ];
  memset( ifconfbuf, 0, sizeof( ifconfbuf ));
  conf.ifc_buf = ifconfbuf;
  conf.ifc_len = sizeof( ifconfbuf );
  if ( ioctl( sock, SIOCGIFCONF, &conf ))
  {
    std::cout << "Unable to obtain MAC address" << std::endl;
    return -1;
  }

  struct ifreq* ifr;
  for (
      ifr = conf.ifc_req;
      reinterpret_cast<char *>(ifr) <
          reinterpret_cast<char *>(conf.ifc_req) + conf.ifc_len;
      ifr++) {
    if ( ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data ) {
      continue;  // duplicate, skip it
    }

    if ( ioctl( sock, SIOCGIFFLAGS, ifr )) {
      continue;  // failed to get flags, skip it
    }
    if ( ioctl( sock, SIOCGIFHWADDR, ifr ) == 0 ) {
      mac = std::string(ifr->ifr_addr.sa_data);
      if (!mac.empty()) {
        break;
      }
    }
  }
  close(sock);

  std::stringstream stream;
  stream << std::hex << HashMacAddressPid(mac);
  *mac_hash = stream.str();

  if (mac_hash->size() > 3) {
    mac_hash->erase(0, mac_hash->size() - 3);
  } else if (mac_hash->size() < 3) {
    *mac_hash = std::string(3 - mac_hash->size(), '0') + *mac_hash;
  }
  return 0;
}



EMSCRIPTEN_BINDINGS() {
  class_<UniqueIdHandler>("UniqueIdHandler")
    .constructor<
    std::mutex *,
    const std::string &
    >()
  ;
};
