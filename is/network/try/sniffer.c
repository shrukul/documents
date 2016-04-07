#include<pcap.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdlib.h> 
#include<sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<netinet/ip_icmp.h>  
#include<netinet/udp.h>  
#include<netinet/tcp.h>  
#include<netinet/ip.h>

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);
void print_ip_header(const u_char * Buffer, int size);

struct sockaddr_in source,dest;
int i,j; 
 
int main()
{
    pcap_if_t *alldevsp , *device;
    pcap_t *handle;
 
    char errbuf[100] , *devname , devs[100][100];
    int count = 1 , n;
     
    printf("Finding available devices ... ");
    if( pcap_findalldevs( &alldevsp , errbuf) == -1 )
    {
        printf("Error finding devices : %s" , errbuf);
        exit(1);
    }
    printf("Done");
     
    printf("\nAvailable Devices are :\n");
    for(device = alldevsp ; device ; device = device->next)
    {
        printf("%d. %s - %s\n" , count , device->name , device->description);
        if(device->name != NULL)
        {
            strcpy(devs[count] , device->name);
        }
        count++;
    }

    printf("Enter the number of the device you want to sniff : ");
    scanf("%d" , &n);
    devname = devs[n];
     
    printf("Opening device %s for sniffing ... " , devname);
    handle = pcap_open_live(devname , 65536 , 1 , 0 , errbuf);
     
    if (handle == NULL) 
    {
        fprintf(stderr, "Couldn't open device %s : %s\n" , devname , errbuf);
        exit(1);
    }
    printf("\n\nHidden String inside packets - \n");

    pcap_loop(handle , 1000 , process_packet , NULL);
    printf("\n\n");
    return 0; 
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
    int size = header->len;
    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));

    if (iph->protocol == 6) // we are concerned with tcp packets
    {   
//        printf("Here");

        struct iphdr *iph = (struct iphdr *)( buffer  + sizeof(struct ethhdr) );
        iphdrlen = iph->ihl*4;
         
        struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));
                 
        int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
             
        print_ip_header(buffer,size);
    }
}

void print_ip_header(const u_char * Buffer, int size)
{
    unsigned short iphdrlen;
         
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    if(iph->tos==7)     // Secret key (byte) field let the dest attacker know that i have sent some information hidden in the header. 
    printf("%c",iph->ttl);
}
