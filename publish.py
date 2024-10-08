import paho.mqtt.client as mqtt
import csv
import time

# MQTT configuration
MQTT_BROKER = "localhost" 
MQTT_PORT = 1883           
MQTT_TOPIC = "sensor/data"


CSV_FILE_PATH = 'E:\Biogas_mornitoring\web\sensor_data.csv'

# Kết nối đến broker MQTT
client = mqtt.Client()
client.connect(MQTT_BROKER, MQTT_PORT, 60)


def publish_csv_data():
    with open(CSV_FILE_PATH, 'r') as csvfile:
        csv_reader = csv.DictReader(csvfile)
        
        for row in csv_reader:
           
            client.publish(MQTT_TOPIC, str(row))
            print(f"Published: {row}")
            time.sleep(1) 

if __name__ == "__main__":
    publish_csv_data()
    client.loop_forever()
