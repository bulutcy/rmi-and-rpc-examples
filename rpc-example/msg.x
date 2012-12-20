/* msg.x: Remote msg printing protocol */
program ASSIGNPROG {
   version ASSIGNMESSAGEVERS {
     string ASSIGNMESSAGE(string) = 1;
   } = 1;
} = 0x20098001;