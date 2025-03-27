import paho.mqtt.client as mqtt

BROKER_ADDRESS = "localhost"
TOPIC = "test/topic"

# Callback when connected
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(TOPIC)

# Callback when a message is received
def on_message(client, userdata, msg):
    print(f"📥 Received: '{msg.payload.decode()}' on topic '{msg.topic}'")

# Create client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER_ADDRESS, 1883, 60)

# Publish some test messages
for i in range(5):
    msg = f"Hello MQTT {i}"
    print(f"📤 Sending: {msg}")
    client.publish(TOPIC, msg)

client.loop_forever()  # Keep listening for incoming messages
