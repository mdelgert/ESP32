Adding and verifying an ENV IV sensor to your AtomU running Tasmota involves the following steps:

### 1. **Connect the Sensor to AtomU**
   - Ensure the ENV IV sensor is correctly wired to the AtomU. Typically, the ENV IV communicates using the I2C protocol. Use the following pins:
     - **SDA** (data line)
     - **SCL** (clock line)
     - **GND** (ground)
     - **3.3V** (power supply)

### 2. **Enable I2C in Tasmota**
   - Log into the Tasmota web interface of your AtomU.
   - Go to **Configuration** > **Configure Module**.
   - Set the **Module Type** to a configuration that supports I2C (e.g., `Generic (18)`).
   - Assign the **GPIO Pins** to I2C SDA and I2C SCL as per your wiring:
     - Set the correct GPIO for SDA to `I2C SDA`.
     - Set the correct GPIO for SCL to `I2C SCL`.
   - Save the settings, and the device will restart.

### 3. **Add the ENV IV Sensor**
   - ENV IV sensors typically support multiple environmental readings (e.g., temperature, humidity, and pressure).
   - Identify the I2C address of the ENV IV sensor. This can usually be found in its datasheet (commonly `0x44` or `0x76`).
   - Configure the sensor in Tasmota:
     - Navigate to **Configuration** > **Configure Other**.
     - In the **Template** field, add a custom template if needed (check Tasmota's documentation for ENV IV-specific templates).
     - Enable the sensor driver that matches your sensor type. For example:
       - `BME280` for temperature, humidity, and pressure.
       - `SHT30` for temperature and humidity.
   - Save the configuration.

### 4. **Verify the Sensor is Detected**
   - Open the Tasmota **Console** from the web interface.
   - Type `I2CScan` and press Enter. Tasmota will scan for connected I2C devices.
     - Verify the ENV IV sensor's address appears in the scan result.
   - If the sensor is detected, Tasmota should automatically start displaying the sensor's readings.

### 5. **Check Sensor Readings**
   - Go to the **Main Page** of the Tasmota web interface.
   - Verify that the environmental data from the sensor (temperature, humidity, pressure) is displayed.
   - Alternatively, monitor the console for live data by typing `teleperiod 10` (sets data reporting interval to 10 seconds) and check the periodic updates.

### 6. **Optional: MQTT Configuration**
   - If you use MQTT to collect data:
     - Configure your MQTT broker under **Configuration** > **Configure MQTT**.
     - Verify that sensor readings are published to the appropriate MQTT topics.

### Troubleshooting
- If the sensor is not detected:
  - Double-check the wiring and power connections.
  - Ensure the sensor's I2C address matches Tasmota's configuration.
  - Confirm that Tasmota firmware includes the necessary drivers for the ENV IV sensor. Update Tasmota if required.
- If readings appear incorrect or incomplete, verify the sensor's compatibility with Tasmota and check for firmware updates.

If your ENV IV sensor is detected and MQTT is connected, you can configure Tasmota to send the sensor data via MQTT using these steps:

---

### 1. **Verify MQTT Configuration**
   - Navigate to **Configuration > Configure MQTT** in the Tasmota web interface.
   - Ensure the following are correctly set:
     - **Host**: Your MQTT broker's IP address or hostname.
     - **Port**: Typically `1883` for unencrypted MQTT or `8883` for encrypted.
     - **Client**: A unique name for your Tasmota device.
     - **User** and **Password**: Credentials for your MQTT broker.
     - **Topic**: Base topic for your Tasmota device, e.g., `atomu`.
     - **Full Topic**: Default is `tasmota/%prefix%/%topic%/`.
       - `%prefix%` is usually `tele`, `stat`, or `cmnd`.
       - `%topic%` is the topic defined above (e.g., `atomu`).
   - Save the settings, and the device will restart.

---

### 2. **Enable Telemetry Reporting**
   - Tasmota sends sensor data via the `tele` prefix by default.
   - In the Tasmota **Console**, type:
     ```plaintext
     teleperiod 300
     ```
     This sets the telemetry reporting interval to 300 seconds (5 minutes). Adjust the interval as needed.

---

### 3. **Verify Sensor Data is Sent**
   - Open your MQTT broker or client (e.g., Mosquitto, MQTT Explorer, or Home Assistant).
   - Subscribe to the telemetry topic for your device:
     ```plaintext
     tele/atomu/SENSOR
     ```
   - You should see JSON messages containing the sensor data. For example:
     ```json
     {
       "Time": "2025-01-01T12:00:00",
       "BME280": {
         "Temperature": 22.3,
         "Humidity": 45.6,
         "Pressure": 1013.4
       }
     }
     ```

---

### 4. **Customize MQTT Payloads (Optional)**
   - If you need custom MQTT messages:
     - Use **Rules** in Tasmota to modify or send specific payloads.
     - In the **Console**, define a rule. For example:
       ```plaintext
       Rule1 ON Tele-BME280#Temperature DO Publish home/atomu/temperature %value% ENDON
       ```
       - Replace `Tele-BME280#Temperature` with the correct telemetry field from your sensor.
       - Replace `home/atomu/temperature` with your desired MQTT topic.
       - `%value%` is a placeholder for the sensor's value.
     - Enable the rule:
       ```plaintext
       Rule1 1
       ```

---

### 5. **Integrate with Home Assistant or Other Systems**
   - For Home Assistant, add the Tasmota integration. If MQTT discovery is enabled, it should automatically detect the device.
   - Alternatively, manually configure the sensor in `configuration.yaml`:
     ```yaml
     sensor:
       - platform: mqtt
         name: "AtomU Temperature"
         state_topic: "tele/atomu/SENSOR"
         value_template: "{{ value_json.BME280.Temperature }}"
         unit_of_measurement: "°C"
       - platform: mqtt
         name: "AtomU Humidity"
         state_topic: "tele/atomu/SENSOR"
         value_template: "{{ value_json.BME280.Humidity }}"
         unit_of_measurement: "%"
     ```

---

### 6. **Test and Monitor**
   - Monitor the sensor readings on your MQTT client or integrated system.
   - Adjust the telemetry interval or MQTT settings if necessary.

---

This setup ensures your ENV IV sensor data is sent to your MQTT broker and can be easily consumed by other systems. Let me know if you encounter any issues!