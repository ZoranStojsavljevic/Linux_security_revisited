### FAQ

#### aa-status reports processes that are unconfined but have a profile defined

Restart the listed processes. Rebooting will also fix the problem.

AppArmor can only track and protect processes that are started after the kernel module has been loaded.
After the apparmor packages have been installed, apparmor will be started. But running processes won't
be protected by AppArmor. Either restarting the processes or rebooting will fix this.

#### How can I enable AppArmor for Firefox?

Since Ubuntu 9.10 (Karmic), AppArmor ships with a profile for Firefox which is disabled by default.

You can enable it using the following command:

	$ sudo aa-enforce /etc/apparmor.d/usr.bin.firefox

#### How do I make AppArmor work with a non-standard HOME directory?

The location of home directories can be tuned in /etc/apparmor.d/tunables/home.

With Ubuntu 10.04 LTS and above, you can set home directory locations using sudo dpkg-reconfigure apparmor.

### Creating a new profile

#### Design a test plan

Try to think about how the application should be exercised. The test plan should be divided into small test
cases. Each test case should have a small description and list the steps to follow.

Some standard test cases are:

	starting the program
	stopping the program
	reloading the program
	testing all the command supported by the init script

In the case of graphical programs, your test cases should also include anything you normally do. Downloading
and opening files, saving files, uploading files, using plugins, saving configurations changes, and launching
other programs are all possibilities.

#### Generate the new profile

Use aa-genprof to generate a new profile.

From a terminal, use the command aa-genprof:

	$ sudo aa-genprof executable

	Example:

	$ sudo aa-genprof slapd

The man page has more information: man aa-genprof.

#### Include your new profile in apparmor-profiles package

To get your new profile included in the apparmor-profiles package, file a bug in Launchpad against the
AppArmor package:

	Include your test plan and testcases.
	Attach your new profile to the bug.
	Migrating an apparmor-profiles profile to a package
	Please see https://wiki.ubuntu.com/ApparmorProfileMigration

### Update profiles

When the program is misbehaving, audit messages are sent to the log files. The program aa-logprof can
be used to scan log files for AppArmor audit messages, review them and update the profiles.

	$ sudo aa-logprof

The man page has more information : man aa-logprof
