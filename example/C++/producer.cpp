#include "globals.hpp"
#include <cstring>
#include <iostream>
#include <kafka/Error.h>
#include <kafka/KafkaProducer.h>
#include <kafka/ProducerCommon.h>
#include <kafka/ProducerRecord.h>
#include <kafka/Properties.h>
#include <kafka/Types.h>


int main(int argc, char * argw[]) {
	using namespace kafka;
	using namespace kafka::clients::producer;
	kafka::Properties props;
	// props.put("bootstrap.servers", globals::brokers);
	props.put("bootstrap.servers", globals::cluster_brokers);
	props.put("enable.idempotence", "true");
	
	KafkaProducer producer(props);

	Callback deliveryCallback = [](const RecordMetadata & metadata, const Error & error){
		if(error) 
			std::cerr << "Failed to delivery message. Reason: " << error.message() << std::endl;
		else
			std::cout << "Message delivered successfully. Metadata: " << metadata.toString() << '\n';
	};
	for(size_t i = 1; i < argc; ++i) {
		ProducerRecord record(globals::topic, NullKey, Value(argw[i], strlen(argw[i])));
		producer.send(record, deliveryCallback);
	}

	return 0;
}
