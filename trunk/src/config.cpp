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
#include <string.h> 
#include <cstdio>  // ok. iostream, i hate u;

using namespace std;

//-----------------------------------------------------------------------------------------------------
void cBot::read_config(string path)
{
	cfg=fopen(path.c_str(),"r");
	
	char buff[300];
	string what;
	string val;
	int i,size;
	while(!feof(cfg))
	{
		fgets(buff,299,cfg);
		if(buff[0] != '#')
		{
			if(buff[0] == 's') //set
			{
				val=""; what="";
				i=4; //set_
					
				while(buff[i]!='=')
				{
					what=what+buff[i];
					i++;
				}
				
				if(buff[i] != '=')  
				{
					cout << "Error parsing config file in: " << what << endl;
					fclose(cfg);					
					die();
				}
				
				i++; // =
				
				if(buff[i] != '"')  
				{
					cout << "Error parsing config file in: " << what << endl;
					fclose(cfg);					
					die();
				}				
				
				i++; // "
				
				size=strlen(buff);
				
				for(; i<size; i++)
				{
					if(buff[i] == '"') break; //end
					if(buff[i]=='\\') i++;
					val=val+buff[i];
				}
				
				if (buff[i]!= '"')  
				{
					cout << "Error parsing config file in: " << what << endl;
					fclose(cfg);
					die();
				}
				
				set(what,val);
				
			}	
			
//-----------		
			else if(buff[0] == 'a') //add
			{
				what="";
				int line,size;
				i=4; //add_
				
				if(buff[i] == 's') //add status
				{
					i=11; //add_status.
				}
				
				while(buff[i]!='=')
				{
					what=what+buff[i];
					i++;
				}
				
				line=atoi(what.c_str());
				i++; // =
				size=strlen(buff);
				parse_status(line, i, buff, size);
			}
			
		}
	
	}
	fclose(cfg);
}

//-----------------------------------------------------------------------------------------------------

void cBot::set(string name, string val)
{


//	switch(name)
//   yea... error: switch quantity not an integer



	if(name == "realname") 					realname=val; 							else
     if(name == "jid")						JID=val;								else
	if(name == "password")					pass=val;								else
	if(name == "owner")						owner=val;							else
	if(name == "server")					server=val;							else
	if(name == "status_lines")				{status_lines=atoi(val.c_str()); 
										_status = new string[atoi(val.c_str())]; }	else	
	if(name == "default_presence_status")		default_presence_status=val;



}


//-----------------------------------------------------------------------------------------------------

void cBot::parse_status(int line, int from, char * buff, int len)
{
	_status[line]="";
	int i=from;
	string var;
	
	if(buff[i] != '"') 
	{
		cout << "Error parsing status in status line " << line << endl;
		fclose(cfg);					
		die();
	
	}
	
	i++;
	for(;i<len; i++)
	{
		if(buff[i] == '"') break;
		else if(buff[i] == '\\') 
		{
			i++;
			_status[line]+=buff[i];
		}
		else if(buff[i] == '$') 
		{
			var="";
			i++; // $			
			while(buff[i] != '$')
			{
				var+=buff[i];	
				i++;
			}
			
			i++; // $
			
			//yeah
#define c(x) if(var==x) {
#define e } else		

c("name")			_status[line]+=realname; e
c("jid")			_status[line]+=JID; e
c("version")		_status[line]+="0.01"; }			

// rest not implemented :P
#undef c
#undef e
			
		}
		else
		{
			_status[line]+=buff[i];
		}
	}
	
	if(buff[i] != '"') 
	{
		cout << "Error parsing status in status line " << line << endl;
		fclose(cfg);					
		die();
	
	}
	


}










