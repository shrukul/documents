#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           
#include <string.h>           

#include <netdb.h>            
#include <sys/types.h>        
#include <sys/socket.h>       
#include <netinet/in.h>      
#include <netinet/ip.h>       
#define __FAVOR_BSD           // Use BSD format of tcp header
#include <netinet/tcp.h>      
#include <arpa/inet.h>        
#include <sys/ioctl.h>        
#include <bits/ioctls.h>      
#include <net/if.h>           

#include <errno.h>            

#define IP4_HDRLEN 20         // IPv4 header length
#define TCP_HDRLEN 20         // TCP header length, excludes options data

// Function prototypes
uint16_t checksum (uint16_t *, int);
uint16_t tcp4_checksum (struct ip, struct tcphdr);
char *allocate_strmem (int);
uint8_t *allocate_ustrmem (int);
int *allocate_intmem (int);

int send_p (char c);

int main()
 {
    char *arr;
    int i=0,size;
    
    char c[1000];
    FILE *fptr;
    if ((fptr=fopen("program.txt","r"))==NULL)
     {
       printf("Error! File doesn't exist!");
       exit(1);
     }

    printf("Using wlan0 as interface\n");
	
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    rewind(fptr);
    arr = malloc(size * (sizeof(char)));
    fread(arr, sizeof(char), size, fptr);
    fclose(fptr);

    while(i<strlen(arr))
     send_p(arr[i++]);
 }

int send_p (char c)
{
  int i, status, sd, *ip_flags, *tcp_flags;
  const int on = 1;
  char *interface, *target, *src_ip, *dst_ip;
  struct ip iphdr;
  struct tcphdr tcphdr;
  uint8_t *packet;
  struct addrinfo hints, *res;
  struct sockaddr_in *ipv4, sin;
  struct ifreq ifr;
  void *tmp;

  packet = allocate_ustrmem (IP_MAXPACKET);
  interface = allocate_strmem (40);
  target = allocate_strmem (40);
  src_ip = allocate_strmem (INET_ADDRSTRLEN);
  dst_ip = allocate_strmem (INET_ADDRSTRLEN);
  ip_flags = allocate_intmem (4);
  tcp_flags = allocate_intmem (8);

  strcpy (interface, "wlan0");

  if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    perror ("Failed to create socket()");
    exit (1);
  }

  memset (&ifr, 0, sizeof (ifr));
  snprintf (ifr.ifr_name, sizeof (ifr.ifr_name), "%s", interface);
  if (ioctl (sd, SIOCGIFINDEX, &ifr) < 0) {
    perror ("ioctl() failed to find interface ");
    return (EXIT_FAILURE);
  }

  close (sd);

//  printf ("Interface %s ID %i\n", interface, ifr.ifr_ifindex);
    printf("Sending %c\n",c);

  strcpy (src_ip, "127.0.0.1");

  strcpy (target, "127.0.0.1");

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = hints.ai_flags | AI_CANONNAME;

  // Resolve target using getaddrinfo().
  if ((status = getaddrinfo (target, NULL, &hints, &res)) != 0) {
    fprintf (stderr, "getaddrinfo() failed: %s\n", gai_strerror (status));
    exit (EXIT_FAILURE);
  }

  ipv4 = (struct sockaddr_in *) res->ai_addr;
  tmp = &(ipv4->sin_addr);
  if (inet_ntop (AF_INET, tmp, dst_ip, INET_ADDRSTRLEN) == NULL) {
    status = errno;
    exit (1);
  }
  freeaddrinfo (res);

  iphdr.ip_hl = IP4_HDRLEN / sizeof (uint32_t);
  iphdr.ip_v = 4;
  iphdr.ip_tos = 7;
  iphdr.ip_len = htons (IP4_HDRLEN + TCP_HDRLEN);
  iphdr.ip_id = htons (0);
  ip_flags[0] = 0;
  ip_flags[1] = 0;
  ip_flags[2] = 0;
  ip_flags[3] = 0;
  iphdr.ip_off = htons ((ip_flags[0] << 15)
                      + (ip_flags[1] << 14)
                      + (ip_flags[2] << 13)
                      +  ip_flags[3]);

  // We hide data here, in time to live
  iphdr.ip_ttl = c;

  iphdr.ip_p = IPPROTO_TCP;

  if ((status = inet_pton (AF_INET, src_ip, &(iphdr.ip_src))) != 1) {
    exit (1);
  }

  if ((status = inet_pton (AF_INET, dst_ip, &(iphdr.ip_dst))) != 1) {
    exit (1);
  }

  iphdr.ip_sum = 0;
  iphdr.ip_sum = checksum ((uint16_t *) &iphdr, IP4_HDRLEN);

  tcphdr.th_sport = htons (60);
  tcphdr.th_dport = htons (80);
  tcphdr.th_seq = htonl (0);
  tcphdr.th_ack = htonl (0);
  tcphdr.th_x2 = 0;
  tcphdr.th_off = TCP_HDRLEN / 4;
  tcp_flags[0] = 0;
  tcp_flags[1] = 1;
  tcp_flags[2] = 0;
  tcp_flags[3] = 0;
  tcp_flags[4] = 0;
  tcp_flags[5] = 0;
  tcp_flags[6] = 0;
  tcp_flags[7] = 0;

  tcphdr.th_flags = 0;
  for (i=0; i<8; i++) {
    tcphdr.th_flags += (tcp_flags[i] << i);
  }

  tcphdr.th_win = htons (65535);
  tcphdr.th_urp = htons (0);
  tcphdr.th_sum = tcp4_checksum (iphdr, tcphdr);

  memcpy (packet, &iphdr, IP4_HDRLEN * sizeof (uint8_t));
  memcpy ((packet + IP4_HDRLEN), &tcphdr, TCP_HDRLEN * sizeof (uint8_t));

  memset (&sin, 0, sizeof (struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = iphdr.ip_dst.s_addr;

  if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    exit (EXIT_FAILURE);
  }

  if (setsockopt (sd, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on)) < 0) {
    exit (EXIT_FAILURE);
  }

  if (setsockopt (sd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof (ifr)) < 0) {
    exit (EXIT_FAILURE);
  }

  if (sendto (sd, packet, IP4_HDRLEN + TCP_HDRLEN, 0, (struct sockaddr *) &sin, sizeof (struct sockaddr)) < 0)  {
    exit (EXIT_FAILURE);
  }

  close (sd);

  free (packet);
  free (interface);
  free (target);
  free (src_ip);
  free (dst_ip);
  free (ip_flags);
  free (tcp_flags);

  return (0);
}

// Computing the internet checksum (RFC 1071).
uint16_t checksum (uint16_t *addr, int len)
{
  int count = len;
  register uint32_t sum = 0;
  uint16_t answer = 0;

  while (count > 1) {
    sum += *(addr++);
    count -= 2;
  }

  if (count > 0) {
    sum += *(uint8_t *) addr;
  }

  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  answer = ~sum;

  return (answer);
}

uint16_t tcp4_checksum (struct ip iphdr, struct tcphdr tcphdr)
{
  uint16_t svalue;
  char buf[IP_MAXPACKET], cvalue;
  char *ptr;
  int chksumlen = 0;

  ptr = &buf[0];

  memcpy (ptr, &iphdr.ip_src.s_addr, sizeof (iphdr.ip_src.s_addr));
  ptr += sizeof (iphdr.ip_src.s_addr);
  chksumlen += sizeof (iphdr.ip_src.s_addr);

  memcpy (ptr, &iphdr.ip_dst.s_addr, sizeof (iphdr.ip_dst.s_addr));
  ptr += sizeof (iphdr.ip_dst.s_addr);
  chksumlen += sizeof (iphdr.ip_dst.s_addr);

  *ptr = 0; ptr++;
  chksumlen += 1;

  memcpy (ptr, &iphdr.ip_p, sizeof (iphdr.ip_p));
  ptr += sizeof (iphdr.ip_p);
  chksumlen += sizeof (iphdr.ip_p);

  svalue = htons (sizeof (tcphdr));
  memcpy (ptr, &svalue, sizeof (svalue));
  ptr += sizeof (svalue);
  chksumlen += sizeof (svalue);

  memcpy (ptr, &tcphdr.th_sport, sizeof (tcphdr.th_sport));
  ptr += sizeof (tcphdr.th_sport);
  chksumlen += sizeof (tcphdr.th_sport);

  memcpy (ptr, &tcphdr.th_dport, sizeof (tcphdr.th_dport));
  ptr += sizeof (tcphdr.th_dport);
  chksumlen += sizeof (tcphdr.th_dport);

  memcpy (ptr, &tcphdr.th_seq, sizeof (tcphdr.th_seq));
  ptr += sizeof (tcphdr.th_seq);
  chksumlen += sizeof (tcphdr.th_seq);

  memcpy (ptr, &tcphdr.th_ack, sizeof (tcphdr.th_ack));
  ptr += sizeof (tcphdr.th_ack);
  chksumlen += sizeof (tcphdr.th_ack);

  cvalue = (tcphdr.th_off << 4) + tcphdr.th_x2;
  memcpy (ptr, &cvalue, sizeof (cvalue));
  ptr += sizeof (cvalue);
  chksumlen += sizeof (cvalue);

  memcpy (ptr, &tcphdr.th_flags, sizeof (tcphdr.th_flags));
  ptr += sizeof (tcphdr.th_flags);
  chksumlen += sizeof (tcphdr.th_flags);

  memcpy (ptr, &tcphdr.th_win, sizeof (tcphdr.th_win));
  ptr += sizeof (tcphdr.th_win);
  chksumlen += sizeof (tcphdr.th_win);

  *ptr = 0; ptr++;
  *ptr = 0; ptr++;
  chksumlen += 2;

  memcpy (ptr, &tcphdr.th_urp, sizeof (tcphdr.th_urp));
  ptr += sizeof (tcphdr.th_urp);
  chksumlen += sizeof (tcphdr.th_urp);

  return checksum ((uint16_t *) buf, chksumlen);
}

char *allocate_strmem (int len)
{
  void *tmp;

  tmp = (char *) malloc (len * sizeof (char));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (char));
    return (tmp);
  } else {
    exit (1);
  }
}

// Allocate memory for an array of unsigned chars.
uint8_t *allocate_ustrmem (int len)
{
  void *tmp;

  tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (uint8_t));
    return (tmp);
  } else {
    exit (1);
  }
}

int *allocate_intmem (int len)
{
  void *tmp;

  tmp = (int *) malloc (len * sizeof (int));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (int));
    return (tmp);
  } else {
    exit (1);
  }
}
