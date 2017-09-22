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


void errormsg(char *lsd) {
	perror(lsd);
	exit(1);
}
// safe mid
inline std::string breakup(std::string &source, size_t start) {
    std::string rt;
    for(size_t i = start; source[i] != 0 && i < start+255; i++)
    rt += source[i];
    return rt;
}

inline std::string trim(std::string &s) {
   std::string rt;
   for(size_t i = 0; i < s.length(); i++) 
   if(s[i] != '\n')
   rt += s[i];
   return rt;
}

inline std::string ls2str(std::string dir) {
	std::string rt;
	DIR *d;
	struct dirent *e;
	struct stat sb;

	if((d = opendir(dir.c_str())) == 0) {
		std::cerr << "Error couldnt open directory.\n";
		return "{error invalid directory}";
	}
	
	chdir(dir.c_str());
	while((e = readdir(d)) != 0) {
		lstat(e->d_name,&sb);
		if(S_ISDIR(sb.st_mode)) {
			if(e->d_name[0] == '.' || strcmp(".", e->d_name) == 0 || strcmp("..", e->d_name) == 0)
			continue;
			rt += "[";
			rt += std::string(e->d_name) + "]\n";
			
		}
		else 
		     rt += std::string(e->d_name) + "\n";
	}
	closedir(d);
	return rt;
}

inline bool chk(int sock, int rt) {
	if(rt < 0) {
		perror("A error has occoured:");
		close(sock);
		return false;
	}
	return true;
}

std::string pw = "";
std::string cur_dir = "";
std::string ag = "";
bool logz = false;
std::fstream log_file;

inline void getInfo() {
	std::fstream file;
	file.open("ip2ip.conf", std::ios::in);
	if(file.is_open()) {
		std::getline(file,pw);
		std::getline(file,cur_dir);
		file.close();
	} else {
		std::cerr << "Error couldnt load configuration file.\n";
		exit(1);
		return;
	}
}

std::string Get() {
	std::fstream file;
	file.open("info.txt", std::ios::in );
	std::string rt_val = "";
	if(file.is_open()) {
		while(!file.eof()) {
		 	std::string line;
			std::getline(file,line);
			if(rt_val.length() + line.length() > 255)
			return rt_val;
			rt_val += line + "\n";
		}
		
		file.close();
		return rt_val;
	}
	std::cerr << "Error Couldnt Find info.\n";
	exit(1);
	return "";
}

int proc_serv(int nsock, std::string there_ip) {
	std::string current_directory = cur_dir;
        int rt_val = 0;
	static char buffer[256];
	bzero(buffer,sizeof(buffer));
	std::cout << "Connection succesfully established .. \n";
	rt_val = read(nsock,buffer,sizeof(buffer));
	if(!chk(nsock,rt_val)) return 1;
	std::string buf = buffer;
	if(buf.find("ip2ip") != -1) {
		std::cout << buffer << "\n";
		bzero((char*)buffer, sizeof(buffer));
		sprintf(buffer,"password:");
		rt_val = write(nsock,buffer,sizeof(buffer));
		if(!chk(nsock,rt_val)) return 1;
		bzero((char*)buffer, sizeof(buffer));
		rt_val = read(nsock, buffer, sizeof(buffer));
		if(chk(nsock,rt_val) && std::strstr(buffer,pw.c_str())) {
			std::cout << "Password accepted. sending info.\n";
			log_file << there_ip << ": Password Accepted\n";
			bzero((char*)buffer, sizeof(buffer));
			strncpy(buffer, ag.c_str(),ag.length());
			rt_val = write(nsock, buffer, sizeof(buffer));
			if(!chk(nsock, rt_val)) {
				return 1;
			}
			bzero((char*)buffer,sizeof(buffer));
			while(true) {
				std::cout << "Waiting for response..\n";
				rt_val = read(nsock, buffer, sizeof(buffer));
				if(!chk(nsock, rt_val)) 
				return 1;
				std::string cmd = buffer;
				log_file << there_ip << ": command:  " << cmd;
				std::cout << cmd;
				 if(cmd.find("get ") != -1) {
				        std::string filename = cmd.substr(cmd.find("get ")+4, cmd.length());
					std::string fname = current_directory + "/" + filename;
					std::fstream file;
					fname = trim(fname);
					file.open(fname.c_str(),std::ios::binary | std::ios::in);
					
					bzero((char*)buffer, sizeof(buffer));
					std::cout << "Sending file [" << fname << "]\n";
					log_file << there_ip << ": getting file" << fname << "\n";
					if(file.is_open())  {
						file.seekg(0,std::ios::end);
						size_t len = file.tellg();
						file.seekg(0,std::ios::beg);
						filename = trim(filename);
						sprintf(buffer,"%s<%d", filename.c_str(), len);
						rt_val = write(nsock, buffer, sizeof(buffer));
						if(!chk(nsock, rt_val)) {
							file.close();
							return 1;	
						}
						std::cout << "Total Bytes to read: " << len << "\n";
						
						int read_bytes = 0;
						 static char buf[256];
					        while(!file.eof()) {
						    
						     bzero((char*)buf,sizeof(buf));
						     if(len < 256) {
						     	file.read((char*)buf,len);
							rt_val = write(nsock, buf, sizeof(buf));
							if(!chk(nsock, rt_val))
							return 1;
							break;
						     }
						    
						     if(read_bytes == len) 
						     break;
						     file.read((char*)buf, sizeof(buf));
						     read_bytes = file.tellg();
						     rt_val = write(nsock, buf, sizeof(buf));
						     
						     std::cout << "Read bytes: { " << rt_val << "} " << read_bytes << "/" << len << "\n";
						     
						     if(!chk(nsock,rt_val)) {
						     	file.close();
							return 1;
						     }
						     if((read_bytes =file.tellg()) == -1)
						     break;
						} 
						file.close();
						bzero((char*)buf, sizeof(buf));
						sprintf(buf,"@all done");
						rt_val = write(nsock, buf, sizeof(buf));
						printf("file successfully transfered.\n");
						continue;
					} else {
						file.close();
						sprintf(buffer,"{Error file not found or could not opened.}");
						rt_val = write(nsock, buffer, sizeof(buffer));
						if(!chk(nsock,rt_val))
						return 1;
						continue;
					}
				
				} else if(cmd.find("cd ") != -1) {
					std::string ro = cmd.substr(cmd.find("cd ")+3, cmd.length());
					ro = trim(ro);
					if(cmd.find("..") != -1) {
						if(current_directory == cur_dir) {
						 	bzero((char*)buffer,sizeof(buffer));
							sprintf(buffer,"{Access Denied.}");
							rt_val = write(nsock, buffer, sizeof(buffer));
							if(!chk(nsock,rt_val))
							return 1;
							continue;
						}
					        if(current_directory.length()>2)
						current_directory = current_directory.substr(0,current_directory.rfind("/"));
						if(current_directory.length()<2)
						current_directory = cur_dir;
						bzero((char*)buffer, sizeof(buffer));
						sprintf(buffer, "#%s", current_directory.c_str());
						rt_val = write(nsock, buffer, sizeof(buffer));
						if(!chk(nsock,rt_val)) return 1;
						continue;
					}
					
					std::string cur_d = current_directory + "/" + ro;
					std::cout << "cd to [" << cur_d << "]\n";
					if(ls2str(cur_d).find("{") == -1) {
						current_directory = cur_d;
						bzero((char*)buffer, sizeof(buffer));
						if(ro.length() < 254) {
							sprintf(buffer,"#%s", ro.c_str());
							rt_val = write(nsock, (char*)buffer, sizeof(buffer));
							if(!chk(nsock,rt_val))
							return 1;
							
						}
						else {
							sprintf(buffer, "{Error invalid directory. too long! }");
							rt_val = write(nsock, (char*)buffer,sizeof(buffer));
							if(!chk(nsock,rt_val)) return 1;
						}
						continue;
						
					}
					else {
						bzero((char*)buffer,sizeof(buffer));
						sprintf(buffer,"{Error invalid directory name.}");
						rt_val = write(nsock, buffer, sizeof(buffer));
						if(!chk(nsock,rt_val))
						return 1;
						continue;
					}
						
				
				} else if(cmd.find("ls") != -1) {
				      bzero((char*)buffer, sizeof(buffer));
				      std::string dir_info = ls2str(current_directory);
				      std::cout << " Sending Directory Listing ... size := " << dir_info.length() << "{\n";
				      sprintf(buffer,"%s:%d", current_directory.c_str(),dir_info.length());
				      rt_val = write(nsock, buffer, sizeof(buffer));
				      if(!chk(nsock, rt_val))
				      return 1;
				      unsigned long bytes_sent = 0;
				      bzero((char*)buffer, sizeof(buffer));
				      std::string leftOf = dir_info;
				      if(dir_info.length() > 255)  {
					do {
					    static char buff[256];
					    bzero((char*)buff, sizeof(buff));
					    std::string cur_tok = breakup(leftOf, bytes_sent);
					    std::cout << cur_tok;
					    strncpy(buff, cur_tok.c_str(), sizeof(buff));
					    rt_val = write(nsock, buff, sizeof(buff));
					    if(!chk(nsock, rt_val)) return 1;
					    bytes_sent += 255;
					    } while( bytes_sent < dir_info.length() ); 
				      }
				      else {
				      sprintf(buffer,"%s", dir_info.c_str());
				      rt_val = write(nsock, buffer, sizeof(buffer));
				      if(!chk(nsock,rt_val))
				      return 1;
				      std::cout << dir_info;
				      
				      } 
				      
				      std::cout << "\n}\n";
				
				      
				
				} else if(cmd.find("exit.") != -1) {
					bzero((char*)buffer, sizeof(buffer));
					sprintf(buffer,"$");
					rt_val = write(nsock, buffer, sizeof(buffer));
					sleep(2);
					close(nsock);
					return 0;
				} 
				 else {
				   bzero((char*)buffer, sizeof(buffer));
				   sprintf(buffer," {Error invalid command.}");
				   rt_val = write(nsock, buffer, sizeof(buffer));
				   if(!chk(nsock, rt_val))
				   return 1;
				   }
				
				
			}
		}
		else {
			std::cout << "Error invalid password closing connection.\n";
			return 1;
		}
		
	}
     close(nsock);
     return 0;
}

int con_count = 0;

int start_listen(int &tsock, int port) {
	std::cout << "Listening on Port: " << port << "\n";
	int sock = socket(AF_INET,SOCK_STREAM,0), nsock = 0;
	
	if(sock < 0) 
		errormsg("Error creating socket..");
	
	static struct sockaddr_in addy;
	bzero((char*)&addy,sizeof(addy));
	
	addy.sin_port = htons(port);
	addy.sin_family = AF_INET;
	addy.sin_addr.s_addr = INADDR_ANY;
	int yup = 1;
	if(setsockopt(sock, SOL_SOCKET,SO_REUSEADDR,&yup,sizeof(yup)) < 0)
	 errormsg("Error setting socket option (SO_REUSEADDR)");
	  
	
	if(bind(sock, (struct sockaddr *)&addy, sizeof(addy)) < 0)
	errormsg("bind ");
	
	
		
	if(listen(sock,5) < 0)
		errormsg("Error on listen.");
	
	while( true ) {
	
	
	
	static socklen_t caddy_len;
	static struct sockaddr_in caddy;
	std::cout << "Waiting for incoming connections..\n";
	nsock = accept(sock, (struct sockaddr *)&caddy, &caddy_len);
	char *buff = inet_ntoa(caddy.sin_addr);
	std::string there_ip = buff;;
	std::cout << "Connection Accepted from: " << there_ip << " connection number: " << ++con_count << "\n";
	log_file << "Connection Accepted from: " << there_ip << "\n";
	int rc_val = 0;
	
	// wait for incoming connections.
	if(nsock < 0)
		errormsg("Error on accept:");
		int pid = fork();
		if(pid == 0) {
		proc_serv(nsock, there_ip);
		std::cout << "Connection to: " << there_ip << " Terminated.\n";
		exit(0);
		}
		else 
			continue;
		
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc == 2 ||  argc == 3) {
		getInfo();
		ag = Get();
		if(argc == 3 && strcmp(argv[2], "-log") == 0) {
			logz = true;
			std::cout << "Loggin enabled log file: log.txt\n";
			log_file.open("log.txt", std::ios::app | std::ios::out );
		}
		std::cout << "Current working directory: " << cur_dir << "\n";
		std::cout << ag << "\n";
		int port_num = atoi(argv[1]);
		int rt = 0;
		int tsock;
		
		if(port_num != 0 && (rt = start_listen(tsock, port_num)) == 0) {
			log_file.close();
			return rt;
		}
		else
		std::cerr << "Error invalid port number, or internal error!\n";
	}
	else
		std::cerr << "Error invalid arguments correct syntax is: ip2ipfserv_server port\n";
	return 0;
}
