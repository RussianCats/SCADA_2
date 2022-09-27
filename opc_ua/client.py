from opcua import Client
import time
from random import randint
import os
from sys import argv


script, IP, PORT = argv

url = f"opc.tcp://{IP}:{PORT}"



client = Client(url)

client.connect()

print("Client Connected")

while True:

    Temp = client.get_node("ns=2;i=4")
    #T = randint(10,50)
    Temperature = Temp.get_value()
    print(Temperature)
    os.system(f"echo '{Temperature}' > /tmp/pipe_opcua  ")
    time.sleep(0.1)

    Press = client.get_node("ns=2;i=3")
    #P = randint(200,999)
    Pressure = Press.get_value()
    print(Pressure)
    os.system(f"echo '{Pressure}' > /tmp/pipe_opcua  ")
    time.sleep(0.1)

    Hum = client.get_node("ns=2;i=5")
    #T = datetime.datetime.now()
    Humidity = Hum.get_value()
    print(Humidity)
    os.system(f"echo '{Humidity}' > /tmp/pipe_opcua  ")
    time.sleep(0.1)

    time.sleep(1)
