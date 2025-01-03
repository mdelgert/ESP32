To add a serial device (e.g., `/dev/ttyACM0`) to a Proxmox container (CT), follow these steps:

### 1. **Verify the Serial Device**
Ensure the device is recognized on the Proxmox host:
```bash
ls -l /dev/ttyACM0
```

If the device exists, you’ll see it listed. Note its permissions and ownership.

---

### 2. **Stop the Container**
Stop the container before making configuration changes:
```bash
pct stop <CT_ID>
```

Replace `<CT_ID>` with your container ID.

---

### 3. **Add the Serial Device**
Edit the container's configuration file, located at:
```bash
/etc/pve/lxc/<CT_ID>.conf
```

Add the following line to map the host's serial device to the container:
```bash
lxc.cgroup2.devices.allow: c 166:* rwm
lxc.mount.entry: /dev/ttyACM0 dev/ttyACM0 none bind,create=file
```

- `166` is the major device number for `/dev/ttyACM0`. You can verify it using `ls -l /dev/ttyACM0` (the first number in the major:minor pair).
- Adjust permissions if necessary (e.g., `rw` for read-write).

---

### 4. **Restart the Container**
Start the container:
```bash
pct start <CT_ID>
```

---

### 5. **Check the Serial Device in the Container**
Log into the container and verify that `/dev/ttyACM0` is available:
```bash
ls -l /dev/ttyACM0
```

---

### 6. **Test the Device**
Use a tool like `minicom`, `screen`, or custom software to test communication with the serial device.

---

### Notes:
- Ensure the container has access to the required group (e.g., `dialout`) for the device.
- You may need to adjust the container's apparmor profile if access is restricted.
- For persistent permissions, consider using `udev` rules on the host.