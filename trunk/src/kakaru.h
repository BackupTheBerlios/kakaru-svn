/***************************************************************************
 *   Copyright (C) 2004 by senu                                            *
 *   senu@o2.pl                                                            *
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
#define I_HAVE_KAKARU_H
#include <string>

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <jabberoo.hh>
#include <judo.hpp>

#ifdef I_WANNA_SEE_WARNINGS
#warning TODO: check, std::vector and handmade list (class{class * next};) times
#warning TODO: parse group file
#warning TODO: repair cLog;
#warning TODO: put pointers to thelp instead of  5 * this same thelp :/
#warning TODO: wtf?!? wit set_presence?!? maybe memtest86? 
#endif

//----ENUMS----

#define ctCHAT 0
#define ctMESSAGE 1

#define stUNAVAILABLE 0
#define stDND 1
#define stAWAY 2
#define stXD 3
#define stAVAILABLE 4

//----ENUMS----



using namespace std;
using namespace jabberoo;

class cBot;

struct warn_level
{
	short int level; // 1 - normal; 2 - warning; 3 - fatal 
};

struct thelp
{
	string name, syntax, body;
};



class cLog
{
   public:
   	cLog(string, short int);
	~cLog();
	cLog& operator<<(int);
	cLog& operator<<(string);	
	cLog& operator<<(warn_level);
   private:
	short int gWhere;   
   
   protected:
   	FILE * log_file;
	string temp;
	string timestamp(void);
	string itoa(int);	

};

class cBot
{
   public:
 	struct tgroup
	{
		string name;
		vector <thelp> helps;
		vector <string> users;
	} * groups;
	
	string pass;
    	string JID;
    	string server;
	string owner;
	string default_presence_status;
	string realname;
	int status_lines;	
	string * _status;
	
	void read_groups(string);

	int connect(string, string, string); //tmp
	int close();
	int send_message(int,string, string);
	int get_messages();     
	void set_presence(int, string);
	void die();	
	void cBot::die(string);
	void do_command(string, string, string);
 		
   	void read_config(string);
	
       
   private:
   
   protected:
     void parse_status(int, int, char *, int);   
	void status(string, string); 
	void say(string, string); 	
	void parse_presence(string, string); 	
	void say_to(string, string); 	
	void say_to_all(string, string);
	int get_group(string);
	thelp get_gelp(int,string);
   	bool check_command(int,string);
	void add_user(int, string);
	void add_help(int, string, string, string);	
	void set(string,string);		
	string timestamp();	
   	FILE * cfg;
	

};





