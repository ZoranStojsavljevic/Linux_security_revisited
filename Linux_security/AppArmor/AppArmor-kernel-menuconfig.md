## AppArmor

### What is AppArmor?

AppArmor is MAC style security extension for the Linux kernel. It implements a task centered policy, with
task “profiles” being created and loaded from user space. Tasks on the system that do not have a profile
defined for them run in an unconfined state which is equivalent to standard Linux DAC permissions.

### AppArmor .config options in security options menuconfig

  │ Symbol: DEFAULT_SECURITY_APPARMOR [=y]
  │ Type  : bool
  │ Prompt: AppArmor
  │   Location:
  │     -> Security options
  │ (1)   -> First legacy 'major LSM' to be initialized (<choice> [=y])
  │   Defined at security/Kconfig:270
  │   Depends on: <choice>
  │
  │
  │ Symbol: SECURITY_APPARMOR [=y]
  │ Type  : bool
  │ Prompt: AppArmor support
  │   Location:
  │ (2) -> Security options
  │   Defined at security/apparmor/Kconfig:2
  │   Depends on: SECURITY [=y] && NET [=y]
  │   Selects: AUDIT [=y] && SECURITY_PATH [=y] && SECURITYFS [=y] && SECURITY_NETWORK [=y]
  │
  │
  │ Symbol: SECURITY_APPARMOR_DEBUG [=n]
  │ Type  : bool
  │ Prompt: Build AppArmor with debug code
  │   Location:
  │     -> Security options
  │ (3)   -> AppArmor support (SECURITY_APPARMOR [=y])
  │   Defined at security/apparmor/Kconfig:41
  │   Depends on: SECURITY_APPARMOR [=y]
  │
  │
  │ Symbol: SECURITY_APPARMOR_DEBUG_ASSERTS [=n]
  │ Type  : bool
  │ Prompt: Build AppArmor with debugging asserts
  │   Location:
  │     -> Security options
  │       -> AppArmor support (SECURITY_APPARMOR [=y])
  │ (4)     -> Build AppArmor with debug code (SECURITY_APPARMOR_DEBUG [=n])
  │   Defined at security/apparmor/Kconfig:51
  │   Depends on: SECURITY_APPARMOR_DEBUG [=n]
  │
  │
  │ Symbol: SECURITY_APPARMOR_DEBUG_MESSAGES [=n]
  │ Type  : bool
  │ Prompt: Debug messages enabled by default
  │   Location:
  │     -> Security options
  │       -> AppArmor support (SECURITY_APPARMOR [=y])
  │ (5)     -> Build AppArmor with debug code (SECURITY_APPARMOR_DEBUG [=n])
  │   Defined at security/apparmor/Kconfig:61
  │   Depends on: SECURITY_APPARMOR_DEBUG [=n]
  │
  │
  │ Symbol: SECURITY_APPARMOR_HASH [=y]
  │ Type  : bool
  │ Prompt: Enable introspection of sha1 hashes for loaded profiles
  │   Location:
  │     -> Security options
  │ (6)   -> AppArmor support (SECURITY_APPARMOR [=y])
  │   Defined at security/apparmor/Kconfig:18
  │   Depends on: SECURITY_APPARMOR [=y]
  │   Selects: CRYPTO [=y] && CRYPTO_SHA1 [=y]
  │
  │
  │ Symbol: SECURITY_APPARMOR_HASH_DEFAULT [=y]
  │ Type  : bool
  │ Prompt: Enable policy hash introspection by default
  │   Location:
  │     -> Security options
  │       -> AppArmor support (SECURITY_APPARMOR [=y])
  │ (7)     -> Enable introspection of sha1 hashes for loaded profiles (SECURITY_APPARMOR_HASH [=y])
  │   Defined at security/apparmor/Kconfig:28
  │   Depends on: SECURITY_APPARMOR_HASH [=y]

### How to enable/disable

	set CONFIG_SECURITY_APPARMOR=y

If AppArmor should be selected as the default security module then set:

	CONFIG_DEFAULT_SECURITY_APPARMOR=y

### Build the kernel

If AppArmor is not the default security module it can be enabled by passing security=apparmor on the
kernel’s command line.

If AppArmor is the default security module it can be disabled by passing apparmor=0, security=XXXX
(where XXXX is valid security module), on the kernel’s command line.

For AppArmor to enforce any restrictions beyond standard Linux DAC permissions policy must be loaded
into the kernel from user space (see the Documentation and tools links).

### How To Install "apparmor" Package on Ubuntu

	$ sudo apt-get update -y
	$ sudo apt-get install -y apparmor
	$ sudo apt-get install -y apparmor-utils (optional)

Check the system logs to confirm that there are no related errors.

### Documentation

Documentation can be found on the wiki, linked below.

#### Mailing List
apparmor@lists.ubuntu.com

#### Wiki
http://apparmor.wiki.kernel.org/

#### User space tools
https://launchpad.net/apparmor

#### Kernel module
git://git.kernel.org/pub/scm/linux/kernel/git/jj/apparmor-dev.git
