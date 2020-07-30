## Fedora32 SELinux Examples

### SELinux config file

Configuration file location: /etc/selinux/config

	[vuser@fedora32-ssd ~]$ cat /etc/selinux/config

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


	[vuser@fedora32-ssd selinux ~]$

The variable SELINUX can have three values:

	[1] SELINUX=disabled
	[2] SELINUX=permissive
	[3] SELINUX=enforcing

### Common SELinux commands

#### Fedora32 sestatus example

SELinux status tool: # sestatus

	[vuser@fedora32-ssd tftpboot]$ sestatus
	SELinux status:			enabled
	SELinuxfs mount:		/sys/fs/selinux
	SELinux root directory:		/etc/selinux
	Loaded policy name:		targeted
	Current mode:			enforcing
	Mode from config file:		enforcing
	Policy MLS status:		enabled
	Policy deny_unknown status:	allowed
	Memory protection checking:	actual (secure)
	Max kernel policy version:	32
	[vuser@fedora32-ssd tftpboot]$ mount | grep selinux
	selinuxfs on /sys/fs/selinux type selinuxfs (rw,relatime)
	[vuser@fedora32-ssd tftpboot]

#### Fedora32 semanage -l example

	[root@fedora32-ssd tftpboot]# semanage login -l

	Login Name           SELinux User         MLS/MCS Range        Service

	__default__          unconfined_u         s0-s0:c0.c1023       *
	root                 unconfined_u         s0-s0:c0.c1023       *
	[root@fedora32-ssd tftpboot]#

#### Fedora32 chcat -L example

	[root@fedora32-ssd tftpboot]# chcat -L
	s0                             SystemLow
	s0-s0:c0.c1023                 SystemLow-SystemHigh
	s0:c0.c1023                    SystemHigh
	[root@fedora32-ssd tftpboot]#

### Fedora32 tftpd server example

#### Fedora32 tftp-server status

	[root@fedora32-ssd tftpboot]# systemctl status tftp-server
	● tftp-server.service - Tftp Server
		Loaded: loaded (/etc/systemd/system/tftp-server.service; enabled; vendor preset: disabled)
		Active: active (running) since Sat 2020-07-11 15:13:58 CEST; 2s ago
	TriggeredBy: ● tftp-server.socket
		Docs: man:in.tftpd
		Main PID: 33379 (in.tftpd)
		Tasks: 1 (limit: 14184)
		Memory: 480.0K
		CPU: 4ms
	CGroup: /system.slice/tftp-server.service
		└─33379 /usr/sbin/in.tftpd -c -p -s /var/lib/tftpboot

	Jul 11 15:13:58 fedora32-ssd systemd[1]: Started Tftp Server.
	[root@fedora32-ssd tftpboot]#

#### Fedora32 tftp-server ls -alZ example

	[root@fedora32-ssd tftpboot]# pwd
	/var/lib/tftpboot
	[root@fedora32-ssd tftpboot]# ls -al
	total 196064
	drwxr-xr-x.  2 root  root          4096 May  4 01:06 .
	drwxr-xr-x. 83 root  root          4096 Jul 10 14:21 ..
	-rw-r--r--.  1 root  root         60292 Jul  5 06:19 am335x-boneblack.dtb
	-rw-r--r--.  1 root  root         57292 Jun 22 13:29 am335x-boneblack.dtb-5.2.5-jumpnow
	-rw-r--r--.  1 root  root         60292 Jun 30 17:29 am335x-boneblack.dtb-5.7.6
	-rw-r--r--.  1 root  root      60332160 Jun 22 13:29 core-image-minimal-beaglebone-20190803131233.rootfs.cpio.xz
	-rw-r--r--.  1 root  root       6210482 Jul  2 18:42 initramfs.cpio.gz
	-rw-r--r--.  1 root  root       3369166 Jul  7 13:28 initramfs.cpio.xz
	-rw-r--r--.  1 root  root       3369230 Jul  7 13:28 initramfs.cpio.xz.uboot
	-rw-r--r--.  1 root  root       6210170 Jul  1 19:01 initramfs.img.uboot
	-rw-r--r--.  1 root  root      52310935 Jun 22 13:29 modules--5.2.5-r0-beaglebone-20190803131233.tgz
	-rw-r--r--.  1 vuser vboxusers 52310935 Jun 22 13:29 modules-beaglebone.tgz
	-rw-r--r--.  1 root  root       1065886 Jul  1 05:37 ramdisk.img.gz
	-rw-r--r--.  1 root  root       1065950 Jul  1 05:38 ramdisk.img.gz.uboot
	-rw-r--r--.  1 root  root       1065950 Jul  3 06:12 ramdisk.img.uboot
	-rw-r--r--.  1 root  root          2089 Jul  1 05:16 README
	-rw-r--r--.  1 root  root           798 Jun 24 12:29 uboot1.sh
	-rw-r--r--.  1 root  root           797 Jul  1 20:15 uboot2.sh
	-rw-r--r--.  1 root  root           801 Jul  2 18:45 uboot.sh
	-rw-r--r--.  1 root  root       4373976 Jul  5 06:19 zImage
	-rw-r--r--.  1 root  root       4472248 Jun 22 13:29 zImage-5.2.5-jumpnow
	-rwxr-xr-x.  1 root  root       4373976 Jun 30 17:25 zImage-5.7.6

	[root@fedora32-ssd tftpboot]# ls -alZ
	total 196064
	drwxr-xr-x.  2 root  root      system_u:object_r:tftpdir_rw_t:s0         4096 May  4 01:06 .
	drwxr-xr-x. 83 root  root      system_u:object_r:var_lib_t:s0            4096 Jul 10 14:21 ..
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0    60292 Jul  5 06:19 am335x-boneblack.dtb
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0    57292 Jun 22 13:29 am335x-boneblack.dtb-5.2.5-jumpnow
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0    60292 Jun 30 17:29 am335x-boneblack.dtb-5.7.6
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0    60332160 Jun 22 13:29 core-image-minimal-beaglebone-20190803131233.rootfs.cpio.xz
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0     6210482 Jul  2 18:42 initramfs.cpio.gz
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0     3369166 Jul  7 13:28 initramfs.cpio.xz
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  3369230 Jul  7 13:28 initramfs.cpio.xz.uboot
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  6210170 Jul  1 19:01 initramfs.img.uboot
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0    52310935 Jun 22 13:29 modules--5.2.5-r0-beaglebone-20190803131233.tgz
	-rw-r--r--.  1 vuser vboxusers unconfined_u:object_r:var_lib_t:s0    52310935 Jun 22 13:29 modules-beaglebone.tgz
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0     1065886 Jul  1 05:37 ramdisk.img.gz
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  1065950 Jul  1 05:38 ramdisk.img.gz.uboot
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  1065950 Jul  3 06:12 ramdisk.img.uboot
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0        2089 Jul  1 05:16 README
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0         798 Jun 24 12:29 uboot1.sh
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0         797 Jul  1 20:15 uboot2.sh
	-rw-r--r--.  1 root  root      unconfined_u:object_r:var_lib_t:s0         801 Jul  2 18:45 uboot.sh
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  4373976 Jul  5 06:19 zImage
	-rw-r--r--.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  4472248 Jun 22 13:29 zImage-5.2.5-jumpnow
	-rwxr-xr-x.  1 root  root      unconfined_u:object_r:tftpdir_rw_t:s0  4373976 Jun 30 17:25 zImage-5.7.6
	[root@fedora32-ssd tftpboot]#

#### Fedora32 tftp-server handling/enabling restorecon example

	[root@fedora32-ssd tftpboot]# /sbin/restorecon -v ramdisk.img.gz.uboot
	Relabeled /var/lib/tftpboot/ramdisk.img.gz.uboot from unconfined_u:object_r:var_lib_t:s0 to unconfined_u:object_r:tftpdir_rw_t:s0
	[root@fedora32-ssd tftpboot]#
