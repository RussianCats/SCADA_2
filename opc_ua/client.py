from opcua import Client
import time
from random import randint


url = "opc.tcp://127.0.0.1:4840"

client = Client(url)

client.connect()

print("Client Connected")

while True:

    Temp = client.get_node("ns=2;i=4")
    #T = randint(10,50)
    Temperature = Temp.get_value()
    print(Temperature)

    Press = client.get_node("ns=2;i=3")
    #P = randint(200,999)
    Pressure = Press.get_value()
    print(Pressure)

    Hum = client.get_node("ns=2;i=5")
    #T = datetime.datetime.now()
    Humidity = Hum.get_value()
    print(Humidity)

    time.sleep(15*60)
