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


#include <kakaru.h>




string cBot::timestamp()
{
	string result;

	return result;
}
 
//-----------------------------------------------------------------------------------------------------
 
void cBot::status(string who, string params)
{
	for(int i=0; i<status_lines; i++) 
	{
		send_message(ctCHAT,who,_status[i]);
	}
 
 
}

//-----------------------------------------------------------------------------------------------------

void cBot::say(string who, string params)
{
	send_message(0,who,params);
}

//-----------------------------------------------------------------------------------------------------

void cBot::do_command(string who, string command, string params)
{
	if(command == "status") 					status(who,params);		else
     if(command == "say")					say(who,params);		else
	if(command == "say_to")					say_to(who,params);		else	
	if(command == "say_to_all")				say_to_all(who,params);		else		
	if(command == "exit")					die("Exited ('/exit') by "+who);		else
	if(command == "set_presence")				parse_presence(who,params);
										
} 
//-----------------------------------------------------------------------------------------------------

void cBot::say_to(string who, string params)
{
	int i=0;
	string group;
	group="";
	
	while(params[i] != ' ')
	{
		group+=params[i];
		params.erase(0);
		i++;	
	}
	
	if (params[i] != ' ')
	{
		say(who,"sorry, i couldn't sent this message. type help say_to");
		return;
	}
	
	params.erase(i); // ' '
	
	params="Message from: [ " + who + " } sent on [ " + timestamp() + ' ' + ']' + '\n' + '\n' +params;
	send_message(0,who,params);
	

}

//-----------------------------------------------------------------------------------------------------

void cBot::say_to_all(string who, string params)
{
	int i=0;
	string group;
	group="";
	
	while(params[i] != ' ')
	{
		group+=params[i];
		params.erase(0);
		i++;	
	}
	
	if (params[i] != ' ')
	{
		say(who,"sorry, i couldn't sent this message. type help say_to_all");
		return;
	}
	
	params.erase(i); // ' '
	
	for(i=0; i<5; i++)
	{
		if(groups[i].name==group)
		{
			i+=10;
		 	break;
		}
	}
	
	if (i < 8) 
	{
		say(who,"sorry, i couldn't sent this message. type help say_to_all");	
		return;
	}
	
	i-=10;
	int size = groups[i].users.size(); 
	
	for(int j=0; j<size; j++)
	{
		params="Message from: [ " + who + " ] sent on [ " + timestamp() + ' ' + ']' + '\n' + '\n' +params;
		send_message(0,groups[i].users[j],params);
	}
	

}

//-----------------------------------------------------------------------------------------------------

void cBot::parse_presence(string who, string params)
{     
	int size=params.size();
	string tmp;
	tmp="";
	for(int i=0;i<size;i++)
	{
		if(params[i]!=' ') 
		{
			tmp=+params[i]; 
			params.erase(0);
		}
		else break;
	}
	set_presence(atoi(tmp.c_str()),params);

	//log << "Presence set to " << params << "( "<< tmp << " )" << G;

}

//-----------------------------------------------------------------------------------------------------
 
