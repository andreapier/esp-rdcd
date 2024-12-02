Import("env")

import os

try:
  from dotenv import load_dotenv
except ImportError:
  env.Execute("$PYTHONEXE -m pip install python-dotenv")
  from dotenv import load_dotenv

from dotenv import load_dotenv

load_dotenv()

wifi_ssid = os.getenv('WIFI_SSID')
wifi_pwd = os.getenv('WIFI_PWD')
wifi_ip = os.getenv('WIFI_IP')
wifi_subnet = os.getenv('WIFI_SUBNET')
wifi_gateway = os.getenv('WIFI_GATEWAY')
wifi_primary_dns = os.getenv('WIFI_PRIMARY_DNS')
wifi_secondary_dns = os.getenv('WIFI_SECONDARY_DNS')

mqtt_client_id = os.getenv('MQTT_CLIENT_ID', 'esp-rdcd')
mqtt_host = os.getenv('MQTT_SERVER')
mqtt_port = os.getenv('MQTT_PORT', 1883)
mqtt_user = os.getenv('MQTT_USERNAME')
mqtt_pwd = os.getenv('MQTT_PWD')

hostname = os.getenv('HOSTNAME', 'esp-rdcd')
pin_pwm = os.getenv('PIN_PWM', 12)
frequency = os.getenv('FREQUENCY', 30000)
max_msg_size = os.getenv('MAX_MSG_SIZE', 7120)

esp_rdcd_env_vars=[
  ("ESP_RDCD_WIFI_SSID", wifi_ssid),
  ("ESP_RDCD_WIFI_PWD", wifi_pwd),
  ("ESP_RDCD_MQTT_CLIENT_ID", mqtt_client_id),
  ("ESP_RDCD_MQTT_SERVER", mqtt_host),
  ("ESP_RDCD_MQTT_PORT", mqtt_port),
  ("ESP_RDCD_MQTT_USERNAME", mqtt_user),
  ("ESP_RDCD_MQTT_PWD", mqtt_pwd),
  ("ESP_RDCD_HOSTNAME", hostname),
  ("ESP_RDCD_PIN_PWM", pin_pwm),
  ("ESP_RDCD_FREQUENCY", frequency),
  ("ESP_RDCD_MAX_MSG_SIZE", max_msg_size)
]

if wifi_ip is not None:
  esp_rdcd_env_vars.append(("ESP_RDCD_WIFI_IP", wifi_ip))
if wifi_subnet is not None:
  esp_rdcd_env_vars.append(("ESP_RDCD_WIFI_SUBNET", wifi_subnet))
if wifi_gateway is not None:
  esp_rdcd_env_vars.append(("ESP_RDCD_WIFI_GATEWAY", wifi_gateway))
if wifi_primary_dns is not None:
  esp_rdcd_env_vars.append(("ESP_RDCD_WIFI_PRIMARY_DNS", wifi_primary_dns))
if wifi_secondary_dns is not None:
  esp_rdcd_env_vars.append(("ESP_RDCD_WIFI_SECONDARY_DNS", wifi_secondary_dns))

env.Append(CPPDEFINES = esp_rdcd_env_vars)