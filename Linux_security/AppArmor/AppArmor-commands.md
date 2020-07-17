## AppArmor
https://help.ubuntu.com/community/AppArmor#List_the_current_status_of_apparmor

### Introduction

AppArmor is a Linux Security Module implementation of name-based access controls. AppArmor confines
individual programs to a set of listed files and posix 1003.1e draft capabilities.

Further information about AppArmor can be found on the AppArmor project's wiki.

### Installation

AppArmor is installed and loaded by default since Ubuntu 8.04 LTS. Some packages will install their
own enforcing profiles. Additional profiles can be found in the package apparmor-profiles from the
Universe repository. When filing bugs against an installed apparmor profile, please see:

https://wiki.ubuntu.com/DebuggingApparmor

### Install additional AppArmor profiles

Enable the Universe repository.

Install apparmor-profiles. Click the link to install, or see InstallingSoftware for more installation
options. 

### Usage

All of the following commands should be executed from a terminal.

#### List the current status of apparmor

	$ sudo aa-status

#### Put a profile in complain mode

	$ sudo aa-complain /path/to/bin

	Example:
	$ sudo aa-complain /bin/ping

#### Put a profile in enforce mode

	$ sudo aa-enforce /path/to/bin

	Example:
	$ sudo aa-enforce /bin/ping

#### Disable AppArmor framework

Systems should not generally need to have AppArmor disabled entirely. It is highly recommended that users
leave AppArmor enabled and put the problematic profile into complain mode (see above), then file a bug
using the procedures found in https://wiki.ubuntu.com/DebuggingApparmor. If AppArmor must be disabled
(eg to use SELinux instead), users can:

	$ sudo systemctl status apparmor
	$ sudo systemctl stop apparmor
	$ sudo systemctl disable apparmor

On Ubuntu systems prior to Ubuntu 16.04 LTS:

	sudo invoke-rc.d apparmor stop
	sudo update-rc.d -f apparmor remove

#### To disable AppArmor in the kernel to either:

	adjust your kernel boot command line (see /etc/default/grub) to include either
	* 'apparmor=0'

	* 'security=XXX' where XXX can be "" to disable AppArmor or an alternative LSM name,
	eg. 'security="selinux"'

	remove the apparmor package with your package manager. Do not 'purge' apparmor if
	you think you might want to reenable AppArmor at a later date

#### Enable AppArmor framework

AppArmor is enabled by default. If you used the above procedures, to disable it, you can re-enable
it by:

Ensure AppArmor is not disabled in /etc/default/grub if using Ubuntu kernels, or if using non-Ubuntu
kernels, that /etc/default/grub has apparmor=1 security=apparmor

#### Ensure that the apparmor package is installed

Enable the systemd unit: sudo systemctl enable apparmor && sudo systemctl start apparmor for systems prior
to Ubuntu 16.04 LTS: 

	$ sudo invoke-rc.d apparmor start
	$ sudo update-rc.d apparmor start 37 S .

#### Reload all profiles

	$ sudo service apparmor reload

#### Reload one profile

	$ sudo apparmor_parser -r /etc/apparmor.d/profile.name

	Example:

	$ sudo apparmor_parser -r /etc/apparmor.d/bin.ping

#### Disable one profile

	$ sudo ln -s /etc/apparmor.d/profile.name /etc/apparmor.d/disable/
	$ sudo apparmor_parser -R /etc/apparmor.d/profile.name

	Example:

	$ sudo ln -s /etc/apparmor.d/bin.ping /etc/apparmor.d/disable/
	$ sudo apparmor_parser -R /etc/apparmor.d/bin.ping

#### Enable one profile

By default, profiles are enabled (ie loaded into the kernel and applied to processes).

	$ sudo rm /etc/apparmor.d/disable/profile.name
	$ sudo apparmor_parser -r /etc/apparmor.d/profile.name

	Example:

	$ sudo rm /etc/apparmor.d/disable/bin.ping
	$ sudo apparmor_parser -r /etc/apparmor.d/bin.ping

The aa-enforce command can also be used to enable a profile:

	$ sudo aa-enforce /etc/apparmor.d/bin.ping

### Profile customization

Profiles can found in /etc/apparmor.d. These are simple text files and can be edited either with a text editor,
or by using aa-logprof.

Some customization can be made in /etc/apparmor.d/tunables/. When updating profiles, it is important to use
these when appropriate. For example, rather than using a rule like:

	/home/*/ r,

use:

	@{HOME}/ r,

After updating a profile, be sure to reload it (see above). 
