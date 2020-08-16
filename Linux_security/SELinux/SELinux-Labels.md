## SELinux Contexts – Labeling Files
https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/6/html/security-enhanced_linux/sect-security-enhanced_linux-working_with_selinux-selinux_contexts_labeling_files

On systems running SELinux, all processes and files are labeled in a way that represents security-relevant
information. This information is called the SELinux context. This is viewed using the ls -Z command:

	$ ls -Z file1
	-rw-rw-r--  user1 group1 unconfined_u:object_r:user_home_t:s0 file1

In this example, SELinux provides a user (unconfined_u), a role (object_r), a type (user_home_t), and a
level (s0). This information is used to make access control decisions. On DAC systems, access is controlled
based on Linux user and group IDs. SELinux policy rules are checked after DAC rules. SELinux policy rules
are not used if DAC rules deny access first.

DAC - Discretionary Access Control	(Pure Linux feature, has nothing to do with SELinux)
MAC - Mandatory Access Control		(SELinux feature)

	$ ls -Z file1
	###	DAC	user  group
	-rw-rw-r--	user1 group1 unconfined_u:object_r:user_home_t:s0	file1
	###	MAC		     a user	  a role   a type      a level
	-rw-rw-r--	user1 group1 unconfined_u:object_r:user_home_t:s0	file1

DAC - Discretionary Access Control	(pure Linux feature)
MAC - Mandatory Access Control		(SELinux feature)

#### Note

By default, newly-created files and directories inherit the SELinux type of their parent directories. For
example, when creating a new file in the /etc/ directory that is labeled with the etc_t type, the new file
inherits the same type:

	$ ls -dZ - /etc/
	drwxr-xr-x. root root system_u:object_r:etc_t:s0	/etc
	# touch /etc/file1
	# ls -lZ /etc/file1
	-rw-r--r--. root root unconfined_u:object_r:etc_t:s0	/etc/file1

There are multiple commands for managing the SELinux context for files, such as chcon, semanage fcontext,
and restorecon.

### Temporary Changes: chcon

The chcon command changes the SELinux context for files. However, changes made with the chcon command do not
survive a file system relabel, or the execution of the restorecon command. SELinux policy controls whether
users are able to modify the SELinux context for any given file. When using chcon, users provide all or part
of the SELinux context to change. An incorrect file type is a common cause of SELinux denying access.

#### Quick Reference

	Run the chcon -t type file-name command to change the file type, where type is a type, such as
	httpd_sys_content_t, and file-name is a file or directory name.

	Run the chcon -R -t type directory-name command to change the type of the directory and its contents,
	where type is a type, such as httpd_sys_content_t, and directory-name is a directory name. 

### Changing a File's or Directory's Type

The following procedure demonstrates changing the type, and no other attributes of the SELinux context. The
example in this section works the same for directories, for example, if file1 was a directory.

Run the cd command without arguments to change into your home directory.
Run the touch file1 command to create a new file. Use the ls -Z file1 command to view the SELinux context for file1:

	$ ls -Z file1
	-rw-rw-r--  user1 group1 unconfined_u:object_r:user_home_t:s0 file1

In this example, the SELinux context for file1 includes the SELinux unconfined_u user, object_r role, user_home_t
type, and the s0 level. For a description of each part of the SELinux context, refer to Chapter 3, SELinux Contexts.

Run the chcon -t samba_share_t file1 command to change the type to samba_share_t. The -t option only changes the
type. View the change with ls -Z file1:

	$ ls -Z file1
	-rw-rw-r--  user1 group1 unconfined_u:object_r:samba_share_t:s0 file1

Use the restorecon -v file1 command to restore the SELinux context for the file1 file. Use the -v option to view
what changes:

	$ restorecon -v file1

restorecon reset file1 context unconfined_u:object_r:samba_share_t:s0->system_u:object_r:user_home_t:s0

In this example, the previous type, samba_share_t, is restored to the correct, user_home_t type. When using targeted
policy (the default SELinux policy in Red Hat Enterprise Linux 6), the restorecon command reads the files in the
/etc/selinux/targeted/contexts/files/ directory, to see which SELinux context files should have.

### Changing a Directory and its Contents Types

The following example demonstrates creating a new directory, and changing the directory's file type (along with its
contents) to a type used by the Apache HTTP Server. The configuration in this example is used if you want Apache HTTP
Server to use a different document root (instead of /var/www/html/):

As the Linux root user, run the mkdir /web command to create a new directory, and then the touch /web/file{1,2,3}
command to create 3 empty files (file1, file2, and file3). The /web/ directory and files in it are labeled with the
default_t type:

	# ls -dZ /web
	drwxr-xr-x  root root unconfined_u:object_r:default_t:s0 /web
	# ls -lZ /web
	-rw-r--r--  root root unconfined_u:object_r:default_t:s0 file1
	-rw-r--r--  root root unconfined_u:object_r:default_t:s0 file2
	-rw-r--r--  root root unconfined_u:object_r:default_t:s0 file3

As the Linux root user, run the chcon -R -t httpd_sys_content_t /web/ command to change the type of the /web/
directory (and its contents) to httpd_sys_content_t:

	# chcon -R -t httpd_sys_content_t /web/
	# ls -dZ /web/
	drwxr-xr-x  root root unconfined_u:object_r:httpd_sys_content_t:s0 /web/
	# ls -lZ /web/
	-rw-r--r--  root root unconfined_u:object_r:httpd_sys_content_t:s0 file1
	-rw-r--r--  root root unconfined_u:object_r:httpd_sys_content_t:s0 file2
	-rw-r--r--  root root unconfined_u:object_r:httpd_sys_content_t:s0 file3

As the Linux root user, run the restorecon -R -v /web/ command to restore the default SELinux contexts:

	# restorecon -R -v /web/
	restorecon reset /web context unconfined_u:object_r:httpd_sys_content_t:s0->system_u:object_r:default_t:s0
	restorecon reset /web/file2 context unconfined_u:object_r:httpd_sys_content_t:s0->system_u:object_r:default_t:s0
	restorecon reset /web/file3 context unconfined_u:object_r:httpd_sys_content_t:s0->system_u:object_r:default_t:s0
	restorecon reset /web/file1 context unconfined_u:object_r:httpd_sys_content_t:s0->system_u:object_r:default_t:s0

Refer to the chcon(1) manual page for further information about chcon.

#### Note

Type Enforcement is the main permission control used in SELinux targeted policy. For the most part,
SELinux users and roles can be ignored.
