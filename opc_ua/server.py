from opcua import Server
from random import randint
import time
import os


server = Server()
url = "opc.tcp://127.0.0.1:4840"
server.set_endpoint(url)

name = "OPCUA_SIMULATION_Server"
addSpace = server.register_namespace(name)

node = server.get_objects_node()

ServerInfo = node.add_object(addSpace, "OPC Simulation Server")
Param = node.add_object(addSpace, "Parameters")

Temp = Param.add_variable(addSpace, "Temperature", 0)
Press = Param.add_variable(addSpace, "Pressure", 0)
Hum = Param.add_variable(addSpace, "Humidity", 0)

Temp.set_writable()
Press.set_writable()
Hum.set_writable()

server.start()
print("Server started at {}".format(url))
print("\nДля выхода введите любое число\n")


def fun():

    while True:
        os.system("cd generator; python gen.py")

        with open('generator/gen.txt', 'r') as file:

            arr_val = [0] * 96

            file = file.readlines()
            i = 0
            for val in file:

                arr_val[i] = list(map(float, val.split("\t")))
                i += 1

            for i in range(96):
                Temperature = arr_val[i][0]
                Pressure = arr_val[i][1]
                Humidity = arr_val[i][2]
                print(Temperature, Pressure, Humidity)

                Temp.set_value(Temperature)
                Press.set_value(Pressure)
                Hum.set_value(Humidity)
                time.sleep(15*60)

            print("\n\nПРОШЛО 24 ЧАСА \n\n")


fun()
