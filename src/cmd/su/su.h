#ifndef _SU_H
#define _SU_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <pwd.h>


#include <security/pam_appl.h>
#ifdef _SU_H
//#include <security/openpam.h>
#else
#include <security/pam_misc.h>
#endif
#include <security/pam_misc.h>


int pam_acct_mgmt(pam_handle_t *pamh, int flags);
int pam_setcred(pam_handle_t *pamh, int flags);
int pam_open_session(pam_handle_t *pamh, int flags);
typedef struct pam_handle pam_handle_t;
int pam_start(const char *service_name, const char *user, const struct pam_conv *pam_conversation, pam_handle_t **pamh);
int pam_authenticate(pam_handle_t *pamh, int flags);
void misc_conv(int num_msg, const struct pam_message **msgm, struct pam_response **response, void *appdata_ptr);
char **pam_getenvlist(pam_handle_t *pamh);
int pam_end(pam_handle_t *pamh, int pam_status);


int setuid(uid_t uid);
struct passwd *getpwuid(uid_t uid);


void fsu(int argc, char const *argv[]);

#endif


