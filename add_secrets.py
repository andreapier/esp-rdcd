Import("env")

import os

try:
  from dotenv import load_dotenv
except ImportError:
  env.Execute("$PYTHONEXE -m pip install python-dotenv")
  from dotenv import load_dotenv

from dotenv import load_dotenv

load_dotenv()

wifi_ssid = os.environ['WIFI_SSID']
wifi_pwd = os.environ['WIFI_PWD']

mqtt_host = os.environ['MQTT_SERVER']
mqtt_port = os.environ['MQTT_PORT']
mqtt_client_id = os.environ['MQTT_CLIENT_ID']
mqtt_user = os.environ['MQTT_USERNAME']
mqtt_pwd = os.environ['MQTT_PWD']

env.Append(CPPDEFINES=[
  ("WIFI_SSID", wifi_ssid),
  ("WIFI_PWD", wifi_pwd),
  
  ("MQTT_SERVER", mqtt_host),
  ("MQTT_PORT", mqtt_port),
  ("MQTT_CLIENT_ID", mqtt_client_id),
  ("MQTT_USERNAME", mqtt_user),
  ("MQTT_PWD", mqtt_pwd)
]) 