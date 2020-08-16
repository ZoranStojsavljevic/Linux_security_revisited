/*
 * Copyright (C) 2020, Zoran Stojsavljevic <zoran.stojsavljevic@gmail.com>
 * SPDX-License-Identifier: GNU General Public License v3.0
 *
 * SEL-bin-policy-path.c was derived from the command: $ man 3 selinux_binary_policy_path
 *
 * To compile and properly link: gcc -lselinux SEL-bin-policy-path.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <selinux/selinux.h>

const char *selinux_path(void);
const char *selinux_policy_root(void);
const char *selinux_binary_policy_path(void);
const char *selinux_current_policy_path(void);
const char *selinux_default_type_path(void);
const char *selinux_failsafe_context_path(void);
const char *selinux_removable_context_path(void);
const char *selinux_default_context_path(void);
const char *selinux_user_contexts_path(void);
const char *selinux_usersconf_path(void);
const char *selinux_x_context_path(void);
const char *selinux_sepgsql_context_path(void);
const char *selinux_netfilter_context_path(void);
const char *selinux_file_context_path(void);
const char *selinux_file_context_local_path(void);
const char *selinux_file_context_homedir_path(void);
const char *selinux_media_context_path(void);
const char *selinux_securetty_types_path(void);
const char *selinux_contexts_path(void);

// Added functionality to show /etc/selinux/config file

int read_selinux_config_file(void) {
	char ch, file_name[] = {"/etc/selinux/config"};
	FILE *fp;

	// printf("SELinux config file: /etc/selinux/config\n");

	fp = fopen(file_name, "r"); // read mode

	if (NULL == fp) {
		perror("Error while opening the file\n");
		exit(EXIT_FAILURE);
	}

	printf("The contents of %s file are:\n", file_name);

	while (EOF != (ch = fgetc(fp))) printf("%c", ch);

	fclose(fp);
	return 0;
}

int main () {
	char str[120];
	const char *buffer;

	buffer = str;

	buffer = selinux_path();
	printf("selinux path is:			%s\n", buffer);
	buffer = selinux_policy_root();
	printf("selinux policy root is:			%s\n", buffer);
	buffer = selinux_binary_policy_path();
	printf("selinux binary policy path is:		%s\n", buffer);
	buffer = selinux_current_policy_path();
	printf("selinux current policy path is:		%s\n", buffer);
	buffer = selinux_default_type_path();
	printf("selinux default type path is:		%s\n", buffer);
	buffer = selinux_failsafe_context_path();
	printf("selinux failsafe context path is:	%s\n", buffer);
	buffer = selinux_removable_context_path();
	printf("selinux removable context path is:	%s\n", buffer);
	buffer = selinux_default_context_path();
	printf("selinux default context path is:	%s\n", buffer);
	buffer = selinux_user_contexts_path();
	printf("selinux user context path is:		%s\n", buffer);
	buffer = selinux_usersconf_path();
	printf("selinux userconf path is:		%s\n", buffer);
	buffer = selinux_x_context_path();
	printf("selinux x context path is:		%s\n", buffer);
	buffer = selinux_sepgsql_context_path();
	printf("selinux sepgsql context path is:	%s\n", buffer);
	buffer = selinux_netfilter_context_path();
	printf("selinux netfilter context path is:	%s\n", buffer);
	buffer = selinux_file_context_path();
	printf("selinux file context path is:		%s\n", buffer);
	buffer = selinux_file_context_local_path();
	printf("selinux file context local path is:	%s\n", buffer);
	buffer = selinux_file_context_homedir_path();
	printf("selinux file context homedir path is:	%s\n", buffer);
	buffer = selinux_media_context_path();
	printf("selinux media context path is:		%s\n", buffer);
	buffer = selinux_securetty_types_path();
	printf("selinux securetty context path is:	%s\n", buffer);
	buffer = selinux_contexts_path();
	printf("selinux context path is:		%s\n", buffer);

	printf("\nShowing SELinux /etc/selinux/config file!\n");
	read_selinux_config_file();
	// Alternative way: system("cat /etc/selinux/config");

	printf("Executing /usr/sbin/sestatus CLI command!\n\n");
	system("sestatus");

	return (0);
}
