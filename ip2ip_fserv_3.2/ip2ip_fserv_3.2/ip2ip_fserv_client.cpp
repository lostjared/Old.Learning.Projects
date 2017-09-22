/***************************************************************************
 *   Copyright (C) 2005 by Jared Bruni                                     *
 *   jared@linux                                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include<iostream>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fstream>
#include<cstring>

inline void errormsg(const char *str) {
        perror(str);
}
inline bool chk(int sock, int rt) {
	if(rt < 0) {
		perror("A error has occoured:");
		close(sock);
		return false;
	}
	return true;
}

int start_connect(std::string ip_addy, int port) {
	int sock, new_socket;
	struct sockaddr_in cli;
	sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(sock < 0) {
		errormsg("Error creating socket!.");
		return -1;
	}
	bzero((char*)&cli, sizeof(cli));
	cli.sin_family = AF_INET;
	cli.sin_port = htons(port);
	cli.sin_addr.s_addr = inet_addr(ip_addy.c_str());
	bool connected = false;
	if(connect(sock,(struct sockaddr*)&cli, sizeof(cli)) < 0) {
		errormsg("Error connecting..");
		close(sock);
		return 0;	
	}
	else
	connected = true;
	
	std::string current_dir = "/";
	
	if(connected == true) {
		int rt_val  = 0;
		static char buffer[256];
		bzero((char*)buffer,sizeof(buffer));
		sprintf(buffer, "ip2ip");
		rt_val = write(sock, buffer, sizeof(buffer));
		bzero((char*)buffer,sizeof(buffer));
		rt_val = read(sock, buffer,sizeof(buffer));
		if(!chk(sock,rt_val))
		return 1;
		if(strstr(buffer,"password:")) {
			printf("Enter Password: ");
			char pw[256];
			bzero((char*)pw, sizeof(pw));
			fgets(pw,255,stdin);
			rt_val = write(sock, pw, sizeof(pw));
			if(!chk(sock,rt_val))
			return 1;
			bzero((char*)buffer,sizeof(buffer));
			rt_val = read(sock, buffer, sizeof(buffer));
			if(!chk(sock,rt_val))
			return 1;
			printf(buffer);
			printf("Accept (y/n):");
			bzero((char*)pw, sizeof(pw));
			fgets(pw,255,stdin);
			if(pw[0] == 'y' || pw[0] == 'Y') {
				while(true) {
				printf("[%s] $ ",current_dir.c_str());
				char cmd[256];
				bzero((char*)cmd,sizeof(cmd));
				fgets(cmd,255,stdin);
				rt_val = write(sock, cmd, sizeof(cmd));
				if(!chk(sock,rt_val))
				return 1;
				bzero((char*)buffer, sizeof(buffer));
				do {
			        rt_val = read(sock,buffer, sizeof(buffer));
				} while(rt_val == 0);
				if(!chk(sock,rt_val))
				return 1;
				std::string buf_cmd = buffer;
				if(buf_cmd.find("$") != -1) {
					close(sock);
					printf("Exiting..\n");
					return 0;
				}
				if(buf_cmd.find("{") != -1) {
					printf("%s\n", buffer);
				}
				else if(buf_cmd.find(":") != -1) {
					std::string rightof;
					rightof = buf_cmd.substr(buf_cmd.rfind(":")+1, buf_cmd.length());
					unsigned long len = atoi(rightof.c_str()),bytes_read = 0;
					printf("Length of directory string: %d\n", len);
					while(true) {
					    bzero((char*)buffer, sizeof(buffer));
					    rt_val = read(sock,buffer,sizeof(buffer));
					    if(!chk(sock,rt_val))
						return 1;
						printf(buffer);
						bytes_read += rt_val;
						if(bytes_read >= len)
						     break;
					    }
					
					printf("\n");
					printf(" Succesfully listed directory.\n");
				}
				else if(buf_cmd.find("#") != -1) {
					std::string cur_dir = buf_cmd.substr(buf_cmd.find("#")+1, buf_cmd.length());
					current_dir = cur_dir;
					continue;
				}
				else if(buf_cmd.find("<") != -1) {
					std::string fname, ts;
					unsigned long total_bytes = 0, bytes_read = 0;
					fname = buf_cmd.substr(0, buf_cmd.find("<"));
					ts = buf_cmd.substr(buf_cmd.find("<")+1, buf_cmd.length());
					printf(" creating File %s of size %s\n", fname.c_str(), ts.c_str());
					total_bytes = atol(ts.c_str());
					if(total_bytes == 0)
					 { std::cout << " no bytes to write!\n"; continue; }					
					std::fstream file;
					file.open(fname.c_str(), std::ios::binary | std::ios::out );
					
					while(file.is_open() && true) {
					
					char data[257];
					bzero((char*)data,sizeof(data));
					rt_val = read(sock,data,256);
					if(!chk(sock,rt_val)) {
						file.close();
						return 1;
					}
					
					if(rt_val > total_bytes) {
						file.write((char*)data,total_bytes);
						file.close();
						std::string m = "chmod 775 ";
						m += fname;
						system(m.c_str());
						std::cout << "Read {" << rt_val << "}" << " : " << bytes_read << " Closing file\n";
						bzero((char*)data,sizeof(data));
						do {
							rt_val = read(sock,(char*)data,256);
						} while( rt_val == 0);
						
						if(strcmp(data,"@all done") == 0)
						std::cout << "File succesfully transfered.\n";
						else
						std::cout << "Error file did not transfer successfully. instead of confirmation I got" << data << "\n";
					 	break;
					}
					
					if(total_bytes-256 <= bytes_read) { 
					        printf("Total Bytes: %d Packet Size: %d Truncation: %d\n", total_bytes, rt_val,total_bytes%bytes_read);
						
						if(bytes_read == total_bytes) {
						file.write((char*)data,rt_val);
						}
						else {
						file.write((char*)data,total_bytes%bytes_read);
						}
						file.close();
						std::string m = "chmod 775 ";
						m += fname;
						system(m.c_str());
						std::cout << "Read {" << rt_val << "}" << " : " << bytes_read << " Closing file\n";
						bzero((char*)data,sizeof(data));
						do {
							rt_val = read(sock,(char*)data,256);
						} while( rt_val == 0);
						
						if(strcmp(data,"@all done") == 0)
						std::cout << "File succesfully transfered.\n";
						else
						std::cout << "Error file did not transfer successfully. instead of confirmation I got" << data << "\n";
					 	break;
					}
					else {
						std::cout << "Read Packet Size {" << rt_val << "}:" << bytes_read << "/" << total_bytes << "\n";
						file.write((char*)data,rt_val);
					}
					
					
					bytes_read += rt_val;
					
				}
				}
				else {
				
				     printf("unknown return from server {%s} of length %d\n",buf_cmd.c_str(), buf_cmd.length()); 
				}
			}
			
		}
		else {
			printf(" Okay you didnt accept so quiting. \n");
			
			close(sock);
			exit(0);
		}
	}
		close(sock);
	}
}

int main(int argc, char *argv[])
{
	if(argc == 3) {
		printf("Welcome to ip2ip fserv.\n");
		start_connect(argv[1],atoi(argv[2]));
		return 0;
	}
	std::cerr << "Error invalid arguments specificed\nCorrect arguments are the following: \n ip2ip_fserv_client ip port\n";
	
	return 0;
}
