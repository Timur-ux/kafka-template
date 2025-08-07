#include "globals.hpp"
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <kafka/Error.h>
#include <kafka/KafkaConsumer.h>
#include <kafka/Properties.h>
#include <kafka/Types.h>

std::atomic_bool isNowRunning{true};

void stopRunning(int sig) {
  if (sig != SIGINT)
    return;
  if (isNowRunning)
    isNowRunning = false;
  else
    signal(SIGINT, SIG_IGN);
}

int main(int argc, char *argw[]) {
  using namespace kafka;
  using namespace kafka::clients::consumer;
  kafka::Properties props;
  props.put("bootstrap.servers", globals::brokers);
  props.put("auto.offset.reset", "earliest");

  signal(SIGINT, stopRunning);

  KafkaConsumer consumer(props);
  consumer.subscribe({globals::topic});

  while (isNowRunning) {
    for (auto records = consumer.poll(std::chrono::seconds{1});
         const auto &record : records) {
			if(record.error()) {
				std::cerr << record.toString() << std::endl;
				continue;
			}

			std::cout << "Message: "<< '\n';
			std::cout << "Topic: " << record.topic() << '\n';
			std::cout << "Key: " << record.key().toString() << '\n';
			std::cout << "Value: " << record.value().toString() << '\n';
			std::cout << "Timestamp: " << record.timestamp().toString() << '\n';
    }
  }

  return 0;
}
