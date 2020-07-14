### How to Enable SELinux

The enabling mechanisms are set in the /etc/selinux/config file.

	[root@fedora32-ssd selinux]# cat /etc/selinux/config

	# This file controls the state of SELinux on the system.
	# SELINUX= can take one of these three values:
	#     enforcing - SELinux security policy is enforced.
	#     permissive - SELinux prints warnings instead of enforcing.
	#     disabled - No SELinux policy is loaded.
	SELINUX=enforcing
	# SELINUXTYPE= can take one of these three values:
	#     targeted - Targeted processes are protected,
	#     minimum - Modification of targeted policy. Only selected processes are protected. 
	#     mls - Multi Level Security protection.
	SELINUXTYPE=targeted


	[root@fedora32-ssd selinux]#

The varialbe SELINUX can have three values, so far known:

	[1] SELINUX=disabled
	[2] SELINUX=permissive
	[3] SELINUX=enforcing

The best reason for assigning permissive rule to SETLINUX is making the operating system accessible while
leaving SeLinux enabled. It’s highly recommended to use the permissive option as it’s hassle free, but it
logs violated rules set in SeLinux.

### How to Disable SELinux

Disabling SELinux is easier as it’s enabled and installed. Basically there are two ways of disabling it.
Either temporarily or permanently. Disabling SeLinux temporary makes it disable for a while until the next
boot, and as soon as the computer is turned on again the state is restarted. On the other hand, the
permanent disable of SeLinux shuts it down completely exposing it to threats out there.

#### Temporarty Disable

The following command on the terminal turns it off temporarily: setenforce 0

#### Permanent Disable

To permanently disabled edit /etc/selinux/config and set SELINUX to disabled. Then mandatory reboot.

### Advanced Options

The advanced options are options which help in extending the functionalities in SELInux. There is tremendous
amount of combinations out there due to the comprehensive nature of SeLinux, so this article lists out some
of the prominent and useful ones among them.

### Role Based Access Control (RBAC)

RBAC allows administrators to switch to a role based way to confine the permission of applications. What it
means is a user of a particular user group is allowed to execute or perform certain predefined actions. As
long as the user is part of the role it’s okay. This is the same thing as switching to root when installing
applications on Linux with administrative rights.

	# semanage login -a -s 'myrole' -r 's0-s0:c0.c1023' <username>

Users can switch their role with the following command.

	$ sudo -r new_role_r -i

Users can also remotely connect to the server via SSH with the role enabled at the startup.

	$ ssh <username>/new_role_r@nucuta.com

### Allow A Service to Listen to a Non-Standard Port

This is quite useful in customizing a service, for instance when a FTP port is changed to a non-standard one
in order to avoid unauthorized accesses, SELinux has to be informed accordingly to allow such ports to pass
through and function as usual. The following example allows the FTP port to listen to 992 port. Likewise, any
service returned by semanage port –l can be replaced.

Some of the popular ports are http_port_t , pop_port_t, ssh_port_t.

	# semanage port -a -t <port to allow> <protocol> <port number>
	# semanage port -a -t ftp_port_t  -p tcp 992
