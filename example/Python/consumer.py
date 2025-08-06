import asyncio
from aiokafka import AIOKafkaConsumer

from globals import BOOTSTRAP_SERVERS, TOPIC_NAME


async def fetch_batch(consumer: AIOKafkaConsumer):
    async for msg in consumer:
        if msg is None:
            print("Waiting...")
        else:
            print(f"Message from {msg.topic}: {msg.key} - {msg.value}")


async def fetch_loop():
    consumer = AIOKafkaConsumer(TOPIC_NAME, bootstrap_servers=BOOTSTRAP_SERVERS, group_id="foobar", auto_offset_reset="earliest")
    await consumer.start()
    try:
        while True:
            await fetch_batch(consumer)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"Stopped due to error: {str(e)}")
    finally:
        await consumer.stop()


if __name__ == "__main__":
    asyncio.run(fetch_loop())
    print("Closing consumer")
