## SSHD Service

### Including PAM (Pluggable Authentication Modules) libraries while compiling/making sshd

	$ ./configure --prefix=/opt --enable-pam --with-pam
	$ make
	$ sudo make install

### sshd.service directory

	File /etc/systemd/system/sshd.service
	sshd.service -> /lib/systemd/system/ssh.service

#### sshd.service example 1

	[Unit]
	Description=OpenBSD Secure Shell server modified to log    
	After=network.target auditd.service sshd.service
	### ConditionPathExists=!/opt/etc/sshd-mod_not_to_be_run
	ConditionPathExists=!/etc/ssh/sshd_not_to_be_run

	[Service]
	EnvironmentFile=-/opt/etc/default/ssh
	ExecStart=/opt/sbin/sshd -D -f /opt/etc/sshd_config $SSHD_OPTS
	ExecReload=/bin/kill -HUP $MAINPID
	KillMode=process
	Restart=on-failure
	RestartPreventExitStatus=255
	Type=notify

	[Install]
	WantedBy=multi-user.target
	Alias=sshd-mod.service

#### sshd.service example 2

	[Unit]
	Description=OpenBSD Secure Shell server
	Documentation=man:sshd(8) man:sshd_config(5)
	After=network.target auditd.service
	ConditionPathExists=!/etc/ssh/sshd_not_to_be_run

	[Service]
	EnvironmentFile=-/etc/default/ssh
	ExecStartPre=/usr/sbin/sshd -t
	ExecStart=/usr/sbin/sshd -D $SSHD_OPTS
	ExecReload=/usr/sbin/sshd -t
	ExecReload=/bin/kill -HUP $MAINPID
	KillMode=process
	Restart=on-failure
	RestartPreventExitStatus=255
	Type=notify
	RuntimeDirectory=sshd
	RuntimeDirectoryMode=0755

	[Install]
	WantedBy=multi-user.target
	Alias=sshd.service

### Some specific problems with sshd service?!

Type of the service could cause the problem... So far, three types of service are known by me:

	Type=forking
	Type=simple
	Type=notify

https://lists.yoctoproject.org/g/yocto/message/49991
