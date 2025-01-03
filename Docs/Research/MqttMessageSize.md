The default size of an MQTT message depends on the MQTT broker and client implementation. Here are some general guidelines:

1. **MQTT Protocol Specification:**
   - MQTT messages can theoretically be up to **256 MB** in size, as the protocol allows for a maximum message size of \( 2^{28} - 1 \) bytes.

2. **Broker Configurations:**
   - Most MQTT brokers impose a default limit to ensure efficient resource usage.
   - Common brokers like **Mosquitto** have a default maximum message size of **256 KB**. This can be configured using the `message_size_limit` parameter.
   - Other brokers may have different defaults, so check the broker's documentation.

3. **Client Library Limitations:**
   - MQTT client libraries may also have a default message size limit. For instance:
     - The **Eclipse Paho** library has no strict default size, but the underlying broker limits apply.
     - Lightweight libraries for microcontrollers may have significantly smaller limits (e.g., 4 KB or 8 KB).

4. **Practical Considerations:**
   - Sending very large messages is generally discouraged as it can lead to inefficiencies, higher latency, and potential memory issues on constrained devices.

To determine or modify the size for your application:
- Check the broker's configuration for the `max_message_size` or equivalent parameter.
- Ensure your client library is configured to handle the message size you intend to send or receive.

In EMQX, the default maximum size for MQTT messages is **1 MB**. This limit is defined by the `max_packet_size` configuration parameter, which specifies the maximum allowed size for MQTT packets. 

It's important to note that this default setting can be adjusted to accommodate specific application requirements. However, increasing the maximum packet size may impact performance, especially in resource-constrained environments. Therefore, any changes to this setting should be carefully evaluated and tested.

Additionally, EMQX imposes a default maximum size of **1 MB** for retained messages. This means that any retained message exceeding this size will be treated as a normal message and not retained. 

For deployments on the EMQX Platform's Premium Plan, the maximum message size is set to **100 KB** and is not adjustable. 

In summary, while the default maximum MQTT message size in EMQX is 1 MB, this setting can be configured to meet the needs of your application. It's essential to consider the potential performance implications when modifying this parameter. 