#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_
#include <string>
namespace globals {
	inline const std::string brokers = "localhost:9092";
	inline const std::string topic = "cpp_topic1";
	inline const std::string cluster_brokers = "localhost:29092,localhost:39092,localhost:49092";
} // namespace globals 
#endif // !GLOBALS_HPP_
