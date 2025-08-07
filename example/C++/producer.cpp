#include <kafka/KafkaProducer.h>
#include <kafka/Properties.h>

namespace kfprod = kafka::clients::producer;

int main(int argc, char * argw[]) {
	kafka::Properties props;
	props.put("bootstrap.servers", "localhost:9092");
	
	kfprod::KafkaProducer producer(props);

	return 0;
}
