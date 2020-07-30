## 43.7. SELinux Policy Overview
https://stuff.mit.edu/afs/athena/project/rhel-doc/5/RHEL-5-manual/Deployment_Guide-en-US/rhlcommon-chapter-0001.html

This chapter is an overview of SELinux policy, some of its internals, and how it works. It discusses
the policy in general terms, while Section 43.8, “Targeted Policy Overview” focuses on the details of
the targeted policy as it ships in Red Hat Enterprise Linux. This chapter starts with a brief overview
of what policy is and where it resides.

Following on from this, the role of SELinux during the boot process is discussed. This is followed by
discussions on file security contexts, object classes and permissions, attributes, types, access
vectors, macros, users and roles, constraints, and a brief discussion summarizing special kernel
interfaces.

### 43.7.1. What is the SELinux Policy?

The SELinux Policy is the set of rules that guide the SELinux security engine. It defines types for
file objects and domains for processes. It uses roles to limit the domains that can be entered, and
has user identities to specify the roles that can be attained. In essence, types and domains are
equivalent, the difference being that types apply to objects while domains apply to processes.

#### 43.7.1.1. SELinux Types

A type is a way of grouping items based on their similarity from a security perspective. This is not
necessarily related to the unique purpose of an application or the content of a document. For example,
a file can have any type of content and be for any purpose, but if it belongs to a user and exists in
that user's home directory, it is considered to be of a specific security type, user_home_t.

These object types are considered alike because they are accessible in the same way by the same set of
subjects. Similarly, processes tend to be of the same type if they have the same permissions as other
subjects. In the targeted policy, programs that run in the unconfined_t domain have an executable file
with a type such as sbin_t. From an SELinux perspective, this means they are all equivalent in terms
of what they can and cannot do on the system.

For example, the binary executable file object at /usr/bin/postgres has the type postgresql_exec_t.
All of the targeted daemons have their own *_exec_t type for their executable applications. In fact,
the entire set of PostgreSQL executables such as createlang, pg_dump, and pg_restore have the same
type, postgresql_exec_t, and they transition to the same domain, postgresql_t, upon execution.

##### 43.7.1.1.1. Using Policy Rules to Define Type Access

The SELinux policy defines various rules which determine how each domain may access each type. Only
what is specifically allowed by the rules is permitted. By default, every operation is denied and
audited, meaning it is logged in the $AUDIT_LOG file. In Red Hat Enterprise Linux, this is set to
/var/log/messages. The policy is compiled into binary format for loading into the kernel security
server, and each time the security server makes a decision, it is cached in the AVC to optimize
performance.

The policy can be defined either by modifying the existing files or by adding local Type Enforcement
(TE) and File Context (FC) files to the policy tree. These new policies can be loaded into the kernel
in real time. Otherwise, the policy is loaded during the boot process by init, as explained in Section
43.7.3, “The Role of Policy in the Boot Process”. Ultimately, every system operation is determined by
the policy and the type-labeling of the files.

##### Important

After loading a new policy, it is recommended that you restart any services that may have new or
changed labeling. Generally speaking, this is only the targeted daemons, as listed in Section 43.8.1,
“What is the Targeted Policy?”.

#### 43.7.1.2. SELinux and Mandatory Access Control

SELinux is an implementation of Mandatory Access Control (MAC). Depending on the security policy type,
SELinux implements either Type Enforcment (TE), Roles Based Access Control (RBAC) or Bell-La Padula
Model Multi-Level Security (MLS).

The policy specifies the rules in the implemented environment. It is written in a language created
specifically for writing security policy. Policy writers use m4 macros to capture common sets of
low-level rules. A number of m4 macros are defined in the existing policy, which facilitate the
writing of new policy. These rules are preprocessed into many additional rules as part of building
the policy.conf file, which is compiled into the binary policy.

Access rights are divided differently among domains, and no domain is required to act as a master
for all other domains. Moving between domains is controlled by the policy, through login programs,
userspace programs such as newrole, or by requiring a new process execution in the new domain. This
movement between domains is referred to as a transition.

### 43.7.2. Where is the Policy?

There are two components to the policy: the binary tree and the source tree. The binary tree is
provided by the selinux-policy-<policyname> package and supplies the binary policy file.

Alternatively, the binary policy can be built from source when the selinux-policy-devel package is
installed.

##### Note

Information on how to edit, write and compile policy is currently outside the scope of this document.

#### 43.7.2.1. Binary Tree Files

	/etc/selinux/targeted/ — this is the root directory for the targeted policy, and contains the
				 binary tree.

	/etc/selinux/targeted/policy/ — this is the location of the the binary policy file policy.<xx>.
					In this guide, the variable SELINUX_POLICY is used for this
					directory.

	/etc/selinux/targeted/contexts/ — this is the location of the security context information and
					  configuration files, which are used during runtime by various
					  applications.

	/etc/selinux/targeted/contexts/files/ — contains the default contexts for the entire file system.
						This is referenced by restorecon when perfoming relabeling
						operations.

	/etc/selinux/targeted/contexts/users/ — in the targeted policy, only the root file is in this
						directory. These files are used for determining context
						when a user logs in. For example, for the root user, the
						context is user_u:system_r:unconfined_t.

	/etc/selinux/targeted/modules/active/booleans* — this is where the runtime Booleans are configured.

##### Note

	These files should never be manually changed. You should use the getsebool, setsebool and semanage
	tools to manipulate runtime Booleans.

#### 43.7.2.2. Source Tree Files

For developing policy modules, the selinux-policy-devel package includes all of the interface files used to
build policy. It is recommended that people who build policy use these files to build the policy modules.

This package installs the policy interface files under /usr/share/selinux/devel/include and has make files
installed in /usr/share/selinux/devel/Makefile.

To help applications that need the various SELinux paths, libselinux provides a number of functions that return
the paths to the different configuration files and directories. This negates the need for applications to
hard-code the paths, especially since the active policy location is dependent on the SELINUXTYPE setting in
/etc/selinux/config.

For example, if SELINUXTYPE is set to strict, the active policy location is under /etc/selinux/strict.

To view the list of available functions, use the following command:

	$ man 3 selinux_binary_policy_path

	DESCRIPTION
	These functions return the paths to the active policy configuration directories and files based on the settings in /etc/selinux/config.

	selinux_path() returns the top-level SELinux configuration directory.
	selinux_policy_root() returns the top-level policy directory.
	selinux_binary_policy_path() returns the binary policy file loaded into kernel.
	selinux_current_policy_path() returns the currently loaded policy file from the kernel.
	selinux_default_type_path() returns the context file mapping roles to default types.
	selinux_failsafe_context_path() returns the failsafe context for emergency logins.
	selinux_removable_context_path() returns the filesystem context for removable media.
	selinux_default_context_path() returns the system-wide default contexts for user sessions.
	selinux_user_contexts_path() returns the directory containing per-user default contexts.
	selinux_usersconf_path() returns the file containing mapping between Linux Users and SELinux users.
	selinux_x_context_path() returns the file containing configuration for XSELinux extension.
	selinux_sepgsql_context_path() returns the file containing configuration for SE-PostgreSQL.
	selinux_netfilter_context_path() returns the default netfilter context.
	selinux_file_context_path() returns the default system file contexts configuration.
	selinux_file_context_local_path() returns the local customization file contexts configuration.
	selinux_file_context_homedir_path() returns the home directory file contexts configuration.
	selinux_media_context_path() returns the file contexts for media device nodes.
	selinux_contexts_path() returns the directory containing all of the context configuration files.
	selinux_securetty_types_path() returns the defines tty types for newrole securettys.

	AUTHOR
	This manual page was written by Dan Walsh <dwalsh@redhat.com>.

##### Note

This man page is available only if you have the libselinux-devel RPM installed.

	[root@fedora32-ssd ~]# dnf install libselinux-devel
	Last metadata expiration check: 1:54:52 ago on Thu 30 Jul 2020 05:36:40 PM CEST.
	Package libselinux-devel-3.0-3.fc32.x86_64 is already installed.
	Dependencies resolved.
	Nothing to do.
	Complete!
	[root@fedora32-ssd ~]#

The use of libselinux and related functions is outside the scope of this document.

##### Please, go to the SELinux-Workshop/ and find the example with libselinux used: SEL-bin-policy-path.c

### 43.7.3. The Role of Policy in the Boot Process

SELinux plays an important role during the early stages of system start-up. Because all processes must be
labeled with their correct domain, init performs some essential operations early in the boot process to
maintain synchronization between labeling and policy enforcement.

	After the kernel has been loaded during the boot process, the initial process is assigned the
	predefined initial SELinux ID (initial SID) kernel. Initial SIDs are used for bootstrapping before
	the policy is loaded.

	/sbin/init mounts /proc/, and then searches for the selinuxfs file system type. If it is present,
	that means SELinux is enabled in the kernel.

	[vuser@fedora32-ssd ~]$ mount | grep selinux
	selinuxfs on /sys/fs/selinux type selinuxfs (rw,relatime)
	[vuser@fedora32-ssd ~]$

	If init does not find SELinux in the kernel, or if it is disabled via the selinux=0 boot parameter,
	or if /etc/selinux/config specifies that SELINUX=disabled, the boot process proceeds with a non-SELinux
	system.

	At the same time, init sets the enforcing status if it is different from the setting in
	/etc/selinux/config. This happens when a parameter is passed during the boot process. The default mode
	is permissive until the policy is loaded, then enforcement is set by the configuration file or by the
	parameters enforcing=0 or enforcing=1.

	If SELinux is present, /selinux/ is mounted.

	The kernel checks /selinux/policyvers for the supported policy version. init instpects /etc/selinux/config
	to determine which policy is active, such as the targeted policy, and loads the associated file at
	$SELINUX_POLICY/policy.<version>.

	If the binary policy is not the version supported by the kernel, init attempts to load the policy file
	if it is a previous version. This provides backward compatibility with older policy versions.

	If the local settings in /etc/selinux/targeted/booleans are different from those compiled in the policy,
	init modifies the policy in memory based on the local settings prior to loading the policy into the kernel.

	By this stage of the process, the policy is fully loaded into the kernel. The initial SIDs are then mapped
	to security contexts in the policy. In the case of the targeted policy, the new domain is
	user_u:system_r:unconfined_t. The kernel can now begin to retrieve security contexts dynamically from the
	in-kernel security server.

	init then re-executes itself so that it can transition to a different domain, if the policy defines it.
	For the targeted policy, there is no transition defined and init remains in the unconfined_t domain.

	At this point, init continues with its normal boot process.

	The reason that init re-executes itself is to accommodate stricter SELinux policy controls. The objective
	of re-execution is to transition to a new domain with its own granular rules. The only way that a process
	can enter a domain is during execution, which means that such processes are the only entry points into
	the domains.

	For example, if the policy has a specific domain for init, such as init_t, a method is required to change
	from the initial SID, such as kernel, to the correct runtime domain for init. Because this transition may
	need to occur, init is coded to re-execute itself after loading the policy.

	This init transition occurs if the domain_auto_trans(kernel_t, init_exec_t, <target_domain_t>) rule is
	present in the policy. This rule states that an automatic transition occurs on anything executing in the
	kernel_t domain that executes a file of type init_exec_t. When this execution occurs, the new process is
	assigned the domain <target_domain_t>, using an actual target domain such as init_t.

### 43.7.4. Object Classes and Permissions

SELinux defines a number of classes for objects, making it easier to group certain permissions by specific
classes. For example:

	File-related classes include filesystem for file systems, file for files, and dir for directories.
	Each class has its own associated set of permissions.

	The filesystem class can mount, unmount, get attributes, set quotas, relabel, and so forth. The file
	class has common file permissions such as read, write, get and set attributes, lock, relabel, link,
	rename, append, etc.

	Network related classes include tcp_socket for TCP sockets, netif for network interfaces, and node
	for network nodes.

	The netif class, for example, can send and receive on TCP, UDP and raw sockets (tcp_recv, tcp_send,
	udp_send, udp_recv, rawip_recv, and rawip_send).

	The object classes have matching declarations in the kernel, meaning that it is not trivial to add
	or change object class details. The same is true for permissions. Development work is ongoing to
	make it possible to dynamically register and unregister classes and permissions.

	Permissions are the actions that a subject can perform on an object, if the policy allows it.
	These permissions are the access requests that SELinux actively allows or denies.
