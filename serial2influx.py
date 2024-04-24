import serial, time
from datetime import datetime


#import rx
from influxdb_client import InfluxDBClient, Point, WritePrecision, WriteOptions
from influxdb_client.client.write_api import SYNCHRONOUS

# Configure InfluxDB connection variables
#token = "nloTTzGPJrlM_a9MwAIGz789f5Y2tEGci5GUYfRskb1GCCRTLBbCXCRHXapQk5cHu3aYAFg1E0Qf2ysY1riTmw=="
token = "IWqHqLCDbvLwv83Hd3a66QFPwKw1m1SrFmFuIWvtzGcijDKRXuFHw6Bvk3gXd4LEJxKtD5Ly1pa2rUXphAGr3w=="
org = "ipl"
bucket = "rover1"
influxip = "192.168.1.7"
_client = InfluxDBClient(url="http://{ip}:8086/".format(ip=influxip), token=token) 
_write_client = _client.write_api()

#Configure the labels for the database
measurement = "sensors"
location = "rover"

try:
    ser = serial.Serial("/dev/ttyACM0")
    while True:
        now = datetime.now()
        timestamp_aq = datetime.timestamp(now)
        iso = datetime.utcnow()
        data = []
        line = str(ser.readline().strip())[2:-1]#srip off some annoying string cruft
        vals = line.split(',')
        print(f"Time: {timestamp_aq}")
        for i,val in enumerate(vals):
            L = chr(i+1+96)
            print(f"Sensor {L}: {val}")
        time.sleep(1)
except KeyboardInterrupt:
    _write_client.__del__()
    _client.__del__()
    pass

