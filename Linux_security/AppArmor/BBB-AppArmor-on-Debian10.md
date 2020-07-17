## Enabling BBB AppArmor on Debian Buster

### Disable permanently BBB SELinux on Debian Buster, if enabled

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

The variable SELINUX can have three values, so far known:

	[1] SELINUX=disabled
	[2] SELINUX=permissive
	[3] SELINUX=enforcing

To disable SELinux, the following should be done (edit the /etc/selinux/config file):

	SELINUX=disabled

Then perform the reboot.

### Install "apparmor" Package on Debian Buster

	$ sudo apt-get update -y
	$ sudo apt-get install -y apparmor
	$ sudo apt-get install -y apparmor-utils (optional)

Check the system logs to confirm that there are no related errors.

#### Example BBB AppArmor installation results

	root@arm:~# sudo apt-get install apparmor
	Reading package lists... Done
	Building dependency tree       
	Reading state information... Done
	Suggested packages:
	  apparmor-profiles-extra apparmor-utils
	The following NEW packages will be installed:
	  apparmor
	0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
	3 not fully installed or removed.
	Need to get 465 kB of archives.
	After this operation, 1,250 kB of additional disk space will be used.
	Get:1 http://deb.debian.org/debian buster/main armhf apparmor armhf 2.13.2-10 [465 kB]
	Fetched 465 kB in 0s (2,035 kB/s)
	Preconfiguring packages ...
	Selecting previously unselected package apparmor.
	(Reading database ... 58159 files and directories currently installed.)
	Preparing to unpack .../apparmor_2.13.2-10_armhf.deb ...
	Unpacking apparmor (2.13.2-10) ...
	Setting up apparmor (2.13.2-10) ...
	[ 1059.480497] audit: type=1400 audit(1594873845.744:2): apparmor="STATUS" operation="profile_load" profile="unconfined" name="nvidia_modprobe" pid=1571 comm="apparmor_parser"
	[ 1059.514666] audit: type=1400 audit(1594873845.768:3): apparmor="STATUS" operation="profile_load" profile="unconfined" name="nvidia_modprobe//kmod" pid=1571 comm="apparmor_parser"
	Created symlink /etc/systemd/system/sysinit.target.wants/apparmor.service → /lib/systemd/system/apparmor.service.
	Reloading AppArmor profiles 
	[ 1066.834617] audit: type=1400 audit(1594873853.099:4): apparmor="STATUS" operation="profile_load" profile="unconfined" name="/usr/sbin/haveged" pid=1631 comm="apparmor_parser"
	[ 1066.875077] audit: type=1400 audit(1594873853.139:5): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="nvidia_modprobe" pid=1632 comm="apparmor_parser"
	[ 1066.908591] audit: type=1400 audit(1594873853.171:6): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="nvidia_modprobe//kmod" pid=1632 comm="apparmor_parser"
	[ 1067.518735] audit: type=1400 audit(1594873853.783:7): apparmor="STATUS" operation="profile_load" profile="unconfined" name="/usr/bin/man" pid=1633 comm="apparmor_parser"
	[ 1067.550268] audit: type=1400 audit(1594873853.807:8): apparmor="STATUS" operation="profile_load" profile="unconfined" name="man_filter" pid=1633 comm="apparmor_parser"
	[ 1067.584231] audit: type=1400 audit(1594873853.811:9): apparmor="STATUS" operation="profile_load" profile="unconfined" name="man_groff" pid=1633 comm="apparmor_parser"
	Setting up dracut (048+80-2) ...
	dracut: Generating /boot/initrd.img-4.19.106-bone49
	depmod: FATAL: could not load /boot/System.map-4.19.106-bone49-interim: No such file or directory
	dracut: Generating /boot/initrd.img-4.19.106-bone49-interim
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	libkmod: ERROR ../libkmod/libkmod.c:586 kmod_search_moddep: could not open moddep file '/lib/modules/4.19.106-bone49-interim//modules.dep.bin'
	dracut: Cannot find module directory /lib/modules/4.19.106-bone49-interim/
	dracut: and --no-kernel was not specified
	dpkg: error processing package dracut (--configure):
	 installed dracut package post-installation script subprocess returned error exit status 1
	dpkg: dependency problems prevent configuration of cryptsetup-initramfs:
	 cryptsetup-initramfs depends on initramfs-tools (>= 0.129) | linux-initramfs-tool; however:
	  Package initramfs-tools is not installed.
	  Package linux-initramfs-tool is not installed.
	  Package initramfs-tools which provides linux-initramfs-tool is not installed.
	  Package dracut which provides linux-initramfs-tool is not configured yet.

	dpkg: error processing package cryptsetup-initramfs (--configure):
	 dependency problems - leaving unconfigured
	dpkg: dependency problems prevent configuration of cryptsetup:
	 cryptsetup depends on cryptsetup-initramfs (>= 2:2.0.3-1); however:
	  Package cryptsetup-initramfs is not configured yet.

	dpkg: error processing package cryptsetup (--configure):
	 dependency problems - leaving unconfigured
	Processing triggers for man-db (2.8.5-2) ...
	Processing triggers for systemd (241-7~deb10u4rcnee0~buster+20200509) ...
	Errors were encountered while processing:
	 dracut
	 cryptsetup-initramfs
	 cryptsetup
	E: Sub-process /usr/bin/dpkg returned an error code (1)
	root@arm:~#

### Enable AppArmor framework

	$ sudo systemctl status apparmor
	$ sudo systemctl start apparmor

#### Example BBB AppArmor enabling results

	root@arm:~# sudo systemctl status apparmor
	● apparmor.service - Load AppArmor profiles
	   Loaded: loaded (/lib/systemd/system/apparmor.service; enabled; vendor preset:
	   Active: inactive (dead)
	     Docs: man:apparmor(7)
	           https://gitlab.com/apparmor/apparmor/wikis/home/

	root@arm:~# sudo systemctl start apparmor
	[ 5670.031550] audit: type=1400 audit(1594878456.064:10): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="/usr/sbin/haveged" pid=4364 comm="apparmor_parser"
	[ 5670.075167] audit: type=1400 audit(1594878456.108:11): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="nvidia_modprobe" pid=4365 comm="apparmor_parser"
	[ 5670.105907] audit: type=1400 audit(1594878456.128:12): apparmor="STATUS" operation="profile_replace" info="same as current profile, skipping" profile="unconfined" name="nvidia_modprobe//kmod" pid=4365 comm="apparmor_parser"
	[ 5670.149922] audit: type=1400 audit(1594878456.172:13): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/usr/bin/man" pid=4366 comm="apparmor_parser"
	[ 5670.204462] audit: type=1400 audit(1594878456.172:14): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="man_filter" pid=4366 comm="apparmor_parser"
	[ 5670.222932] audit: type=1400 audit(1594878456.172:15): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="man_groff" pid=4366 comm="apparmor_parser"

	root@arm:~# sudo systemctl status apparmor
	● apparmor.service - Load AppArmor profiles
	   Loaded: loaded (/lib/systemd/system/apparmor.service; enabled; vendor preset:
	   Active: active (exited) since Thu 2020-07-16 05:47:36 UTC; 11s ago
	     Docs: man:apparmor(7)
	           https://gitlab.com/apparmor/apparmor/wikis/home/
	  Process: 4359 ExecStart=/lib/apparmor/apparmor.systemd reload (code=exited, st
	 Main PID: 4359 (code=exited, status=0/SUCCESS)

	Jul 16 05:47:35 arm systemd[1]: Starting Load AppArmor profiles...
	Jul 16 05:47:36 arm apparmor.systemd[4359]: Restarting AppArmor
	Jul 16 05:47:36 arm apparmor.systemd[4359]: Reloading AppArmor profiles
	Jul 16 05:47:36 arm systemd[1]: Started Load AppArmor profiles.
	root@arm:~#
