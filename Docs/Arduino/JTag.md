https://www.youtube.com/watch?v=b1VkJODi_4w&t=478s
https://zadig.akeo.ie/
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-guides/jtag-debugging/configure-builtin-jtag.html
Invoke-WebRequest 'https://dl.espressif.com/dl/idf-env/idf-env.exe' -OutFile .\idf-env.exe; .\idf-env.exe driver install --espressif

# Restore drive after zadig
https://github.com/pbatard/libwdi/issues/120
FWIW, there is a simple, really simple way of restoring device functionality after this gets mangled by erroneous operations.

Open 'Device Manager' enable 'Show hidden devices' under 'View' and remove any and all greyedout Mouse and USB devices, specifically 'unknown ...'

I guess we don't know all we need to know all the time don't we.

Here is a very helpful page regarding, this may be of use to add to the FAQ for zadig for referral.

https://www.drivethelife.com/windows-10/fix-hid-compliant-mouse-not-working-on-windows-10.html