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


//#warning we should check, std::vector and handmade list (class * next) times
#include <vector>

#include <jabberoo.hh>
#include <judo.hpp>

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
	int set_status(int, string);
	void die();	
	
	void do_command(string, string, string);
 		
   	void read_config(string);
       
   private:
   
   protected:
     void cBot::parse_status(int, int, char *, int);   
	void status(string, string); 
	void say(string, string); 	
	void say_to(string, string); 	
	void cBot::say_to_all(string, string);
	int get_group(string);
	thelp get_gelp(int,string);
   	bool check_command(int,string);
	void add_user(int, string);
	void add_help(int, string, string, string);	
	void set(string,string);		
	string timestamp();	
   	FILE * cfg;
	

};





