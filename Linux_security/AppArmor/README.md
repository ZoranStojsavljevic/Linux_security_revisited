## AppArmor

AppArmor ("Application Armor") is a Linux kernel security module that allows the system administrator
to restrict programs' capabilities with per-program profiles. Profiles can allow capabilities like
network access, raw socket access, and the permission to read, write, or execute files on matching
paths. AppArmor supplements the traditional Unix discretionary access control (DAC) model by providing
mandatory access control (MAC). It has been included in the mainline Linux kernel since version 2.6.36
and its development has been supported by Canonical since 2009. 

### How To Install "apparmor" Package on Ubuntu

	$ sudo apt-get update -y
	$ sudo apt-get install -y apparmor
	$ sudo apt-get install -y apparmor-utils (optional)

Check the system logs to confirm that there are no related errors.
