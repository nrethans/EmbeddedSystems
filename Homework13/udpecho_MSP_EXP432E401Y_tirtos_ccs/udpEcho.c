/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *    ======== udpEcho.c ========
 *    Contains BSD sockets code.
 */

/* BSD support */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>

#include <ti/net/slnetutils.h>

#include "Global.h"

#define UDPPACKETSIZE 1472
#define MAXPORTLEN    6
#define DEFAULT_NET_PORT 1000

extern void fdOpenSession();
extern void fdCloseSession();
extern void *TaskSelf();

typedef struct _my_ip_mreq{
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
} my_ip_mreq;

char *UDPParse(char *buff, struct sockaddr_in *clientAddr, bool todash){
    char *StrBufPTR;
    char *colon;
    int32_t AddrByte;
    uint32_t PortWord;
    char MsgBuff[50];

    StrBufPTR = buff;
    if(!StrBufPTR) return StrBufPTR;
//
    if(MatchSubString(StrBufPTR, "localhost")){
        clientAddr->sin_addr.s_addr = 0x0100007F;
        goto coloncheck;
    }
//    if(MatchSubString(StrBufPTR, "multicast")){
//        clientAddr->sin_addr.s_addr = inet_addr(global.Multicast);
//        goto coloncheck;
//    }
    if(MatchSubString(StrBufPTR, "broadcast")){
        clientAddr->sin_addr.s_addr = 0xFFFFFFFF;
        goto coloncheck;
    }
    if(MatchSubString(StrBufPTR, "nobody")){
        clientAddr->sin_addr.s_addr = 0x00000000;
        goto coloncheck;
    }
    if(isdigit(*StrBufPTR) == 0){
        AddError(NETWORK_ERR, "Message Missing Required Digits");
        return NULL;
    }
    AddrByte = atoi(StrBufPTR);
    clientAddr->sin_addr.s_addr = AddrByte;

    StrBufPTR = strchr(StrBufPTR, '.');
    if(!StrBufPTR) return StrBufPTR;
    StrBufPTR++;
    if(*StrBufPTR == 0) return NULL;
    AddrByte = atoi(StrBufPTR);
    clientAddr->sin_addr.s_addr |= AddrByte << 8;

    StrBufPTR = strchr(StrBufPTR, '.');
    if(!StrBufPTR) return StrBufPTR;
    StrBufPTR++;
    if(*StrBufPTR == 0) return NULL;
    AddrByte = atoi(StrBufPTR);
    clientAddr->sin_addr.s_addr |= AddrByte << 16;

    StrBufPTR = strchr(StrBufPTR, '.');
    if(!StrBufPTR) return StrBufPTR;
    StrBufPTR++;
    if(*StrBufPTR == 0) return NULL;
    AddrByte = atoi(StrBufPTR);
    clientAddr->sin_addr.s_addr |= AddrByte << 24;

coloncheck:
    colon = strchr(StrBufPTR, ':');
    if(!colon){
        PortWord = DEFAULT_NET_PORT;
        StrBufPTR = strchr(StrBufPTR, ' ');
    }
    else{
        StrBufPTR = colon;
        StrBufPTR++;
        if(*StrBufPTR == 0) return NULL;
        if(isdigit(*StrBufPTR) == 0) return NULL;
        PortWord = atoi(StrBufPTR);
    }
    clientAddr->sin_port = (PortWord & 0xFF00) >> 8;
    clientAddr->sin_port |= (PortWord & 0xFF) << 8;

    clientAddr->sin_family = AF_INET;

    if(StrBufPTR){
        if(todash)
            StrBufPTR = strchr(StrBufPTR, '-');
        else
            while(isspace(*StrBufPTR))
                StrBufPTR++;
    }
    return StrBufPTR;

}

void *ListenFxn(void *arg0)
{
    int                bytesRcvd;
    int                status;
    int                server = -1;
    fd_set             readSet;
    struct addrinfo    hints;
    struct addrinfo    *res, *p;
    struct sockaddr_in clientAddr;
    socklen_t          addrlen;
    char               buffer[UDPPACKETSIZE];
    char               portNumber[MAXPORTLEN];
    char               MsgBuff[320];
    int32_t            optval = 1;
    my_ip_mreq         mreq;
    char               *PTR;

    fdOpenSession(TaskSelf());

    sprintf(portNumber, "%d", *(uint16_t *)arg0);
    sprintf(MsgBuff, "-print UDP Recv started : %s", portNumber);
    AddPayload(MsgBuff);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_PASSIVE;

    /* Obtain addresses suitable for binding to */
    status = getaddrinfo(NULL, portNumber, &hints, &res);
    if (status != 0) {
        AddError(NETWORK_ERR, "getaddrinfo() failed");
        goto shutdown;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        server = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (server == -1) {
            continue;
        }

        status = bind(server, p->ai_addr, p->ai_addrlen);
        if (status != -1) {
            break;
        }

        close(server);
    }

    if (server == -1) {
        AddError(NETWORK_ERR, "Socket Not Created");
        goto shutdown;
    } else if (p == NULL) {
        AddError(NETWORK_ERR, "Bind failed");
        goto shutdown;
    } else {
        freeaddrinfo(res);
        res = NULL;
    }

    mreq.imr_multiaddr.s_addr = 0x01FFFFEF; //inet_addr(global.Multicast);

    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    status = setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if(status)
        AddError(NETWORK_ERR, "Socket IP_ADD_MEMBERSHIP to multicast failed");

    status = setsockopt(server, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if(status)
    AddError(NETWORK_ERR, "Socket SO_REUSEPORT to multicast failed");


    do {
        /*
         *  readSet and addrlen are value-result arguments, which must be reset
         *  in between each select() and recvfrom() call
         */
        FD_ZERO(&readSet);
        FD_SET(server, &readSet);
        addrlen = sizeof(clientAddr);

        /* Wait forever for the reply */
        status = select(server + 1, &readSet, NULL, NULL, NULL);

        if (status > 0)
        {
            if (FD_ISSET(server, &readSet))
            {
                bytesRcvd = recvfrom(server, buffer, UDPPACKETSIZE, 0, (struct sockaddr *)&clientAddr, &addrlen);

                if (bytesRcvd > 0)
                {
                    // Pass the received message to AddPayload
                    buffer[bytesRcvd] = '\0'; // Null-terminate the received message

                    if(MatchSubString("-voice", buffer) == true)
                        VoiceParse(buffer);
                    else
                    {
                        sprintf(MsgBuff, "UDP %d.%d.%d.%d> ", (uint8_t)(clientAddr.sin_addr.s_addr)      &0xFF, (uint8_t)(clientAddr.sin_addr.s_addr>> 8) &0xFF, (uint8_t)(clientAddr.sin_addr.s_addr>>16)  &0xFF, (uint8_t)(clientAddr.sin_addr.s_addr>>24) &0xFF);
                        UART_Write_Protected(MsgBuff);
                        UART_Write_Protected(buffer);
                        UART_Write_Protected("\r\n");
                        AddPayload(buffer);
                    }
                }
            }
        }
    } while (status > 0);

shutdown:
    if (res) {
        freeaddrinfo(res);
    }

    if (server != -1) {
        close(server);
    }

    fdCloseSession(TaskSelf());

    return (NULL);
}

void *TransmitFxn(void *arg0)
{
    int                bytesSent;
    int                status;
    int                server = -1;
    fd_set             readSet;
    fd_set             writeSet;
    struct addrinfo    hints;
    struct addrinfo    *res, *p;
    struct sockaddr_in clientAddr;
    socklen_t          addrlen;
    char               portNumber[MAXPORTLEN];
    char*              StrBufPTR;
    int                allow_broadcast = 1;
    uint32_t           gateKey;
    uint32_t           payloadnext;
    int                bytesRequested;

    fdOpenSession(TaskSelf());

    AddPayload("-print UDP Transmit started\n");

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_PASSIVE;

    /* Obtain addresses suitable for binding to */
    status = getaddrinfo(NULL, portNumber, &hints, &res);
    if (status != 0) {
        AddError(NETWORK_ERR,"getaddrinfo() failed");
        goto shutdown;
    }

    for (p = res; p != NULL; p = p->ai_next)
    {
        server = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (server == -1)
            continue;
    }

    if (server == -1)
    {
        AddError(NETWORK_ERR,"Socket not created");
        goto shutdown;
    }
    else //server is valid
    {
        freeaddrinfo(res);
        res = NULL;
    }

    status  = setsockopt(server, SOL_SOCKET, SO_BROADCAST, (void*) &allow_broadcast, sizeof(allow_broadcast));

    while(1){
        /*
         *  readSet and addrlen are value-result arguments, which must be reset
         *  in between each select() and recvfrom() call
         */

        FD_ZERO(&readSet);
        FD_SET(server, &readSet);
        addrlen = sizeof(clientAddr);

        Semaphore_pend(global.Bios.NetSemaphore, BIOS_WAIT_FOREVER);

        status = select(server + 1, NULL, &writeSet, NULL, NULL);

        if(status <= 0)
        {
            AddError(NETWORK_ERR, "Select Server Failed");
            continue;
        }

        bytesSent = -1;
        StrBufPTR = UDPParse(global.NetOutQ.payloads[global.NetOutQ.payloadReading], &clientAddr, true);

        if(StrBufPTR){
            bytesRequested = strlen(StrBufPTR) + 1;
            bytesRequested += global.NetOutQ.binaryCount[global.NetOutQ.payloadReading];

            bytesSent = sendto(server, StrBufPTR, bytesRequested, 0, (struct sockaddr *)&clientAddr, addrlen);
        }

        if(!StrBufPTR){
            AddError(NETWORK_ERR, "UDP Parse Failed");
        }else if(bytesSent < 0 || bytesSent != bytesRequested){
            AddError(NETWORK_ERR, "Sendto() failed");
        }
        gateKey = GateSwi_enter(global.Bios.NetworkGate);
        payloadnext = global.NetOutQ.payloadReading + 1;
        if(payloadnext >= NetQueueLen)
            payloadnext = 0;
        global.NetOutQ.payloadReading = payloadnext;
        GateSwi_leave(global.Bios.NetworkGate, gateKey);
    }

shutdown:
    if (res) {
        freeaddrinfo(res);
    }

    if (server != -1) {
        close(server);
    }

    fdCloseSession(TaskSelf());

    return (NULL);
}
