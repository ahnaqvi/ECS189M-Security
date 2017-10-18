# ECS189M-Security

In covert_channel.c, the goal is to communicate using the file permission bits of a linux configuration file. In practice, this is not always a reliable method of communication since the underlying logic is based on fork which does ensure the order in which the two processes trying to communicate can alter the bits.

The python virus is a simple virus with a constant signature. However, the polymorphic variation uses a simple ROT13 shift on the filename to create a different signature each time.
