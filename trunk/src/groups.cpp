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
#include <jabberoo.hh>
#include <judo.hpp>

using namespace std;
using namespace jabberoo;
using namespace judo;

//-----------------------------------------------------------------------------------------------------

void cBot::read_groups(string path)
{
	
	groups = new tgroup[5];
	
	groups[0].name="general";
	groups[1].name="commanders";
	groups[2].name="lieutenants";
	groups[3].name="sergeants";
	groups[4].name="privates";

	
	add_user(0,"senu@chrome.pl");
	
	add_help(4,"say", "/say message", "The bot will tell you 'message'");
	add_help(4,"status","/status", "Show info about the bot");
	add_help(4,"say_to","/say_to user message", "The bot will send message to user");
	
	add_help(3,"say_to_all","/say_to_all group message", "The bot will send message to group. 'all' means all groups. ");	
	
	add_help(2,"status", "/status", "Show info about the bot");	
	add_help(2,"groups", "/groups group", "Shows users that belong to group. Group can be 'all'");	
	add_help(1,"do", "/do string", "Execute 'string' command. Example: '/do cat /proc/version' will show you Linux kernel version");
	add_help(1,"reload", "/reload integer", "The bot will reload configs, reconnect to the server in integer seconds");
	add_help(1,"rights", "/rights group", "'all' can be used as group. Show vested commands to group");
	add_help(1,"set_status", "/set status integer[0..3] string", "Sets bot status to string, and presence to integer(0-aval, 1-away, 2-dnd, 3-invisible)");
	
	add_help(0,"exit", "/exit integer", "The bot will exit in integer seconds");
	add_help(0,"view_logs", "/view_logs date", "View logs written at date. Date format YYYYMMDD, eg. 20041226");
	

	

//-------------------------------------------------------------	
}

//-----------------------------------------------------------------------------------------------------

void cBot::add_help(int id, string name, string syntax, string body) 
{							// i assume that if sergeants can reload config then general can too
	thelp add_help;
	
	add_help.name=name;
	add_help.syntax=syntax;
	add_help.body=body;

	

	for(int i=0; i<=id; i++)
	{
		groups[i].helps.push_back(add_help);
	}

}

//-----------------------------------------------------------------------------------------------------

void cBot::add_user(int id, string JID)
{
	groups[id].users.push_back(JID);
}

//-----------------------------------------------------------------------------------------------------

int cBot::get_group(string JID) 
{
	int size;		
	
	for(int i=0; i<=4; i++)
	{
		size=groups[i].users.size();	
		for(int j=0; j<size; j++)
		{
			if (groups[i].users[j] == JID)
			{
				return i;
			}
		}
	}

}	

//-----------------------------------------------------------------------------------------------------

thelp cBot::get_gelp(int id,string name)
{
	int size = groups[id].helps.size();	
	
	for(int i=0; i<size; i++)
	{
		if (groups[id].helps[i].name == name)
		{
			return groups[id].helps[i];
		}
	}
	
	thelp default_help;
	
	default_help.name="help";
	default_help.syntax="/help topic";
	default_help.body="Try: help: 'commands', command, 'autor', 'bugs'";
	
	return default_help;

}	

//-----------------------------------------------------------------------------------------------------

bool cBot::check_command(int id, string command) 
{
	int size = groups[id].helps.size();	
	
	for(int i=0; i<size; i++)
	{
		if (groups[id].helps[i].name == command)
		{
			return true;
		}
	}

	return false;
}	

