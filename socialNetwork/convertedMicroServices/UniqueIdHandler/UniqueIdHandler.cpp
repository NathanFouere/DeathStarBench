#include "UniqueIdHandler.hpp"

UniqueIdHandler::UniqueIdHandler(
    std::mutex *thread_lock,
    const std::string &machine_id
) {
    _thread_lock = thread_lock;
    _machine_id = machine_id;
}

UniqueIdHandler::ComposeUniqueId(
    int64_t req_id,
    PostType::type post_type,
    const std::map<std::string, std::string> &carrier
) {
    // Initialize a span
    TextMapReader reader(carrier);
    std::map<std::string, std::string> writer_text_map;
    TextMapWriter writer(writer_text_map);
    auto parent_span = opentracing::Tracer::Global()->Extract(reader);
    auto span = opentracing::Tracer::Global()->StartSpan(
        "compose_unique_id_server", {opentracing::ChildOf(parent_span->get())});
    opentracing::Tracer::Global()->Inject(span->context(), writer);

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
    LOG(debug) << "The post_id of the request " << req_id << " is " << post_id;

    span->Finish();
    return post_id;

}
