/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _MSG_H_RPCGEN
#define _MSG_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define ASSIGNPROG 0x20098001
#define ASSIGNMESSAGEVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define ASSIGNMESSAGE 1
extern  char ** assignmessage_1(char **, CLIENT *);
extern  char ** assignmessage_1_svc(char **, struct svc_req *);
extern int assignprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ASSIGNMESSAGE 1
extern  char ** assignmessage_1();
extern  char ** assignmessage_1_svc();
extern int assignprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_MSG_H_RPCGEN */
