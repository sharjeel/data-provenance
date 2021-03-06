/*
--------------------------------------------------------------------------------
SPADE - Support for Provenance Auditing in Distributed Environments.
Copyright (C) 2011 SRI International

This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <sys/errno.h>
#include <sys/un.h>
#include <assert.h>

#include <spade_reporter_Audit.h>
#include <spade_reporter_Audit_SYSCALL.h>

#define SERVER_PATH     "/dev/audit"
#define BUFFER_LENGTH   10000
#define FALSE           0

#include <android/log.h>
#define LOGERR(...) __android_log_print(ANDROID_LOG_ERROR , "spade-audit", __VA_ARGS__)
#ifdef DEBUG
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , "spade-audit", __VA_ARGS__)
#else
#define LOGD(...)
#endif

#ifdef DEBUG
#ifndef DUMPFILE
#define DUMPFILE "/sdcard/audit-socket-dump.log"
#endif
FILE* fdump;
#endif

// Defining SUN_LEN. Does not exist in Bionic LIBC
#include <string.h>
#define SUN_LEN(ptr) ((size_t) (((struct sockaddr_un *) 0)->sun_path)	\
	+ strlen ((ptr)->sun_path))


int sd = -1, end=0, start=0;
char buffer[BUFFER_LENGTH];
struct sockaddr_un serveraddr;

#ifdef TEST

#define recv(a,b,c,d) simurecv(a,b,c,d)

FILE* dumpinfile = NULL;
int simurecv(int sockfd, void *buf, size_t len, int flags) 
{
  int retcount;
  if(dumpinfile == NULL)
    dumpinfile = fopen("/sdcard/audindump.log", "r");
  if(dumpinfile == NULL)
    return -1;
  retcount = fread(buf, 1, len, dumpinfile);
  return retcount;
}
FILE* stateoutf = NULL;
#endif

/*
 * Class:     spade_reporter_Audit
 * Method:    initAuditStream
 * Signature: ()I
 * Initiates the AF_UNIX socket connection to audit 
 */
JNIEXPORT jint JNICALL Java_spade_reporter_Audit_initAuditStream (JNIEnv *env, jclass j) {
  int rc;

  #ifdef DEBUG
  fdump = fopen(DUMPFILE, "w");
  #endif

  do {
    sd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sd < 0) {
      break;
    }

    memset(&serveraddr, 0, sizeof (serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, SERVER_PATH);

    rc = connect(sd, (struct sockaddr *) &serveraddr, SUN_LEN(&serveraddr)); 

    if (rc < 0) 
      break;
    return 0; // Success
  } 
  while(FALSE);

  if (sd != -1)
    close(sd);

  if (rc == 0)
    return 1;
  return -1;
}

/*
 * Class:     spade_reporter_Audit
 * Method:    readAuditStream
 * Signature: ()Ljava/lang/String;
 * Returns audit logs line by line. If no data is available, it'll make a blocking call and wait for data to arrive
 */
JNIEXPORT jstring JNICALL Java_spade_reporter_Audit_readAuditStream (JNIEnv * env, jclass j_class) {

  int rc;
  assert( sd != -1 ); // Socket already closed ?

#ifdef TEST
  if (stateoutf == NULL )
    stateoutf = fopen("/sdcard/stateout.log", "w");
#endif

  if (start < end)
    {
#ifdef TEST
      fprintf(stateoutf,"\n\n---=== start: %d end: %d  ===---\n\n", start, end);
      fwrite(buffer, 1, BUFFER_LENGTH, stateoutf);
#endif


      int i;
      jstring ret;

      // Return next line from read buffer
      while(buffer[start] == '\n' && start < end) start++; // skip empty lines
      i = start;
      while( i < end && buffer[i] != '\n') i++ ; // Boundary till next EOL
      if (i != end) 
	{
	  // Return a string
	  buffer[i] = '\0';
	  assert ( memmem( &buffer[start], i - start, "\0", 1 ) == NULL );
	  ret = (*env)->NewStringUTF(env,&buffer[start]);
	  start = i + 1;
	  return ret;
	}
      else if (i > BUFFER_LENGTH-100)
	{
	  // Shift buffer back to prevent fragmentation
	  memmove(buffer, buffer + start, end - start);
	  end = end - start;
	  start = 0;
#ifdef TEST
          fprintf(stateoutf, "\n\n---=== Reset Buffer Start: %d End: %d ===---\n\n", start, end);
          fwrite(buffer, 1, end, stateoutf);
          fprintf(stateoutf, "===ENDRESETDUMP---");
#endif
	}
    }
  else 
    {
      // buffer consumed, reset pointers
      start = end = 0;
    }

  // Buffer underflow, read more and retry

  rc = recv(sd, buffer + end, BUFFER_LENGTH - end, 0);
  
  if (rc < 0) {
    Java_spade_reporter_Audit_closeAuditStream(env, j_class);
    // Server closed the connection
    LOGERR("Error while receiving audit stream. Closing connection. ret: %d, errno: %d, buffer-start: %d, buffer-end: %d", rc, errno, start, end);
    return NULL;
  }
  else if (rc == 0) {
    Java_spade_reporter_Audit_closeAuditStream(env, j_class);
    LOGERR("Server closed the connection");
    return NULL;
  }

#ifdef DEBUG
  fwrite(buffer + end, 1, rc, fdump);
#endif

  end += rc;


#ifdef TEST
  fprintf(stateoutf, "\n\n---=== Buffer Underflow. Reread buffer; start: %d end: %d rc: %d ===---\n\n", start, end, rc);
#endif

  return Java_spade_reporter_Audit_readAuditStream(env, j_class);
}

/*
 * Class:     spade_reporter_Audit
 * Method:    readAuditStreamBytes
 * Signature: ()Ljava/lang/String;
 * Returns audit logs from unix socket and returns raw bytes
 */
JNIEXPORT jbyteArray JNICALL Java_spade_reporter_Audit_readAuditStreamRaw (JNIEnv * env, jclass j) {
  int rc;
  assert( sd != -1 ); // Socket already closed ?
  char buf[BUFFER_LENGTH]; 
  rc = recv(sd, buf, BUFFER_LENGTH, 0);
  if (rc < 0) 
    {
      fprintf(stderr, "Connection error: %d", rc);
      return (*env)->NewByteArray(env, 0);
    }
  jbyteArray retArray = (*env)->NewByteArray(env, rc);
  void* retArrayRaw = (*env)->GetPrimitiveArrayCritical(env, (jarray)retArray, NULL);
  if (retArrayRaw == NULL)
    {
      fprintf(stderr, "Out of memory in readAuditStreamRaw!");
      return (*env)->NewByteArray(env, 0);
    }
  memcpy(retArrayRaw, buf, rc);
  (*env)->ReleasePrimitiveArrayCritical(env, (jarray)retArray, retArrayRaw, NULL);
  return retArray;
}

/*
 * Class:     spade_reporter_Audit
 * Method:    closeAuditStream
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_spade_reporter_Audit_closeAuditStream (JNIEnv * env, jclass j_class) {
  #ifdef DEBUG
  fclose(fdump);
  #endif

  if (sd != -1) close(sd);
  return 0;

  #ifdef TEST 
  fclose(dumpinfile);
  fclose(stateoutf);
  #endif 
}


