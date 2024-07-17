# How to create a tap connection between QEMU and linux

To establish a connection between your Linux machine and QEMU without an Ethernet cable or NIC, follow these steps:

### On the Linux Machine

1. Create a TAP port connection:

```bash

ip a add 192.168.1.8/24 dev tap

```

1. Set the TAP port up:

```bash

ip link set tap up

```

1. Verify the connection by running:

```bash

ifconfig

```

You should see the TAP interface listed.
