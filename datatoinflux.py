import socket
import os
import time
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

def server_program():
    host_ip = os.popen('hostname -I').read().strip() # gets the IP address of the host
    print(f"IP Address: {host_ip}")

    host = ''   # leave empty to listen on all available interfaces
    port = 7000  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    server_socket.bind((host, port))  # bind host address and port together
    server_socket.listen(1)
    
    token = os.environ.get("INFLUXDB_TOKEN")
    org = "UTM"
    url = "http://172.17.0.1:8086"
    bucket = "G6"

    client = InfluxDBClient(url=url, token=token, org=org)
    write_api = client.write_api(write_options=SYNCHRONOUS)

    while True:  # continuously listen for connections
        print("Server is listening for incoming connections...")
        conn, address = server_socket.accept()  # accept new connection
        print("Connection from: " + str(address))
        while True:
            data = conn.recv(1024).decode()
            if not data:
                break

            print("Received data: " + str(data))  # This line prints the received data

            # Assuming the data format is "Temperature: XXC, Humidity: YY%"
            parts = data.split(", ")
            if len(parts) != 2 or not parts[0].startswith("Temperature") or not parts[1].startswith("Humidity"):
                continue
                
            temp_str = parts[0].split(": ")[1].split("C")[0]
            humidity_str = parts[1].split(": ")[1].split("%")[0]

            temperature = float(temp_str)
            humidity = float(humidity_str)

            point = Point("DHT_data") \
                .tag("location", "Outdoor") \
                .field("temperature", temperature) \
                .field("humidity", humidity) \
                .time(time.time_ns(), WritePrecision.NS)
            
            write_api.write(bucket=bucket, org=org, record=point)
        conn.close()  # close the connection when client disconnects

if _name_ == '_main_':
    server_program()
