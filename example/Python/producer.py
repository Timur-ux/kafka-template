import asyncio
from aiokafka import AIOKafkaProducer
from globals import *

async def sample_produce(producer: AIOKafkaProducer, key="some", value="none"):
    result = await producer.send_and_wait(TOPIC_NAME, key=key, value=value)
    print(result)

async def main():
    producer = AIOKafkaProducer(bootstrap_servers=BOOTSTRAP_SERVERS, key_serializer=lambda x: x.encode(), value_serializer=lambda x: x.encode())
    await producer.start()
    try:
        while True:
            await sample_produce(producer)
            await asyncio.sleep(5)
    except KeyboardInterrupt:
        pass
    finally:
        await producer.stop()

if __name__ == "__main__":
    asyncio.run(main())
