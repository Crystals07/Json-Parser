#include<bits/stdc++.h>
using namespace std;

#define pp pair<int,int>

class json_parser
{
	public:

		int parser(string);

	private:

		enum JSON_OBJECT_STATE {INITIAL_STATE,START_OF_JSON,AT_START_OF_KEY_STRING,END_OF_KEY_STRING,AT_KEY_VALUE_SEPERATOR,AT_START_OF_STRING_VALUE,
					            END_OF_STRING_VALUE,AT_START_OF_VALUE_NUM,END_OF_VALUE_NUM,AT_START_OF_BOOL_TRUE,AT_END_OF_BOOL_TRUE,		
					            AT_START_OF_BOOL_FALSE,AT_END_OF_BOOL_FLASE,AT_START_OF_NULL_VALUE,AT_END_OF_NULL_VALUE,DEAD_STATE,FINAL_STATE,
					            JSON_ARRAY_END,JSON_OBJECT_END,AT_COMMA};

		enum JSON_ARRAY_STATE {START_STATE,AT_START_JSON_ARRAY,AT_START_JSON_OBJECT,AT_ARRAY_START_STRING,AT_ARRAY_END_STRING,AT_ARRAY_ITEM_SEPERATOR,
		                       AT_START_INT,AT_END_INT,AT_START_BOOL_TRUE,AT_END_BOOL_TRUE,AT_START_BOOL_FALSE,AT_END_BOOL_FALSE,AT_JSON_OBJECT_END,DEAD_STATE_ARRAY,
		                   	    AT_END_NULL_VALUE,FINAL_STATE_ARRAY,AT_COMMA_ARRAY,AT_JSON_ARRAY_END};

		string objstr[20]  =        {"INITIAL_STATE","START_OF_JSON","AT_START_OF_KEY_STRING","END_OF_KEY_STRING","AT_KEY_VALUE_SEPERATOR","AT_START_OF_STRING_VALUE",
					            "END_OF_STRING_VALUE","AT_START_OF_VALUE_NUM","END_OF_VALUE_NUM","AT_START_OF_BOOL_TRUE","AT_END_OF_BOOL_TRUE",		
					            "AT_START_OF_BOOL_FALSE","AT_END_OF_BOOL_FLASE","AT_START_OF_NULL_VALUE","AT_END_OF_NULL_VALUE","DEAD_STATE","FINAL_STATE",
					            "JSON_ARRAY_END","JSON_OBJECT_END","AT_COMMA"};

		string arraystr[18] =       {"START_STATE","AT_START_JSON_ARRAY","AT_START_JSON_OBJECT","AT_ARRAY_START_STRING","AT_ARRAY_END_STRING","AT_ARRAY_ITEM_SEPERATOR",
		                        "AT_START_INT","AT_END_INT","AT_START_BOOL_TRUE","AT_END_BOOL_TRUE","AT_START_BOOL_FALSE","AT_END_BOOL_FALSE","AT_JSON_OBJECT_END","DEAD_STATE_ARRAY",
		                   	    "AT_END_NULL_VALUE","FINAL_STATE_ARRAY","AT_COMMA_ARRAY","AT_JSON_ARRAY_END"};

		pp json_object(string,int);

		pp json_array(string,int);
};


pp json_parser::json_array(string json,int curr)
{
	JSON_ARRAY_STATE curr_state = AT_START_JSON_ARRAY;

	bool flag = true; int indx = curr; 


	int i=curr;

	for(;i<json.size() && flag;i++)
	{	
		cout<<"--> "<<arraystr[curr_state]<<" "<<json[i]<<" "<<i<<endl;

		if(curr_state == START_STATE	)
		{
			if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
	    	{
				curr_state = START_STATE;
		     }

		     else if(json[i]=='[')
		     {
		     	curr_state = AT_START_JSON_ARRAY;
		     }

		     else 
		     {
		     	flag = false;
		     	curr_state = DEAD_STATE_ARRAY;

		     }	
		}

		else if(flag&&curr_state==AT_START_JSON_ARRAY)
		{
			if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
	    	{
				curr_state = AT_START_JSON_ARRAY;
		    }


		    else if(json[i]=='{')
		    {
		    	pp res = json_object(json,i+1);
		    	flag = res.first;
		    	i = res.second;
		    	if(flag) curr_state = AT_JSON_OBJECT_END;
		    }

		    else if(json[i] == '[')
		    {
		    	curr_state = AT_START_JSON_ARRAY;
		    	pp res = json_array(json,i+1);
		    	flag = res.first;
		    	i = res.second;
		    	if(flag) curr_state = AT_JSON_ARRAY_END;
		    }

		    else if(json[i] == ']')
		    {
		    	curr_state = FINAL_STATE_ARRAY;
		    	flag = true;
		    	break;
		    }

		    else if(json[i] == '\"')
		    {
		    	curr_state = AT_ARRAY_START_STRING;
		    }

		    else if(json.substr(i,4) == "true")
		    {
		    	curr_state = AT_END_BOOL_TRUE;
		    	i += 3;
		    }

		    else if(json.substr(i,5) == "false")
		    {
		    	curr_state = AT_END_BOOL_FALSE;
		    	i += 4;
		    }

	    	else if(json[i]>='0'&&json[i]<='9')
	    	{
	    		curr_state = AT_START_INT;
	    	}

	    	else if(json.substr(i,4)=="null")
	    	{
	    		curr_state = AT_END_NULL_VALUE;
	    	}

	    	else
	    	{
	    		flag = false;
	    		curr_state = DEAD_STATE_ARRAY;
	    	}

		 }

		 else if(flag && curr_state == AT_JSON_OBJECT_END)
		 {
		 	if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
	    	{
				curr_state = AT_JSON_OBJECT_END;
		    }

		    else if(json[i] == ',')
		    {
		    	curr_state = AT_COMMA_ARRAY;
		    }

		    else if(json[i] == ']')
		    {
		    	flag = true;
		    	curr_state = FINAL_STATE_ARRAY;
		    	break;
		    }

		    else 
		    {
		    	curr_state = DEAD_STATE_ARRAY;
		    	flag = false;
		    }

		 }

		 else if(flag && curr_state == AT_JSON_ARRAY_END)
		 {
		 	if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
		 	{
		 		curr_state = AT_JSON_ARRAY_END;
		 	}

		 	else if(json[i]==',')
		 	{
		 		curr_state = AT_COMMA_ARRAY;
		 	}

		 	else if(json[i]==']')
		 	{
		 		curr_state = FINAL_STATE_ARRAY;
		 		flag = true;
		 		break;
		 	}

		 	else
		 	{
		 		curr_state = DEAD_STATE_ARRAY;
		 		flag = false;
		 	}

		 }

		 else if(flag && curr_state == AT_ARRAY_START_STRING )
		 {
		 	if(json[i] == '\\')
		 	{
		 		curr_state = AT_ARRAY_START_STRING;
		 		i += 1; 
		 	}

	 		else if(json[i]!='\"')
	 		{
	 			curr_state = AT_ARRAY_START_STRING;
	 		}

	 		else
	 		{
	 			curr_state = AT_ARRAY_END_STRING;
	 		}	
		 }

		 else if(flag && curr_state == AT_ARRAY_END_STRING)
		 {
		 	if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
	    	{
				curr_state = AT_ARRAY_END_STRING;
		    }

		    else if(json[i] == ',')
		    {
		    	curr_state = AT_COMMA_ARRAY;
		    }

		    else if(json[i] == ']')
		    {
		    	curr_state = FINAL_STATE_ARRAY;
		    	flag = true;
		    	break;
		    }

		    else
		    {
		    	curr_state = DEAD_STATE_ARRAY;
		    	flag = false;
		    }

		 }

		 else if(flag && curr_state == AT_START_INT)
		 {
		 	if(json[i]>='0'&&json[i]<='9'||json[i] == '-')
		 	{
		 		curr_state = AT_START_INT;
		 	}

		 	else if(json[i] == ' '||json[i] == '\n' || json[i] == '\t' )
		 	{
		 		curr_state = AT_END_INT;
		 	}

		 	else if(json[i] == ',')
		 	{
		 		curr_state = AT_COMMA_ARRAY;
		 	}

		 	else 
		 	{
		 		flag = false;
		 		curr_state = DEAD_STATE_ARRAY;

		 	}
		 }

		 else if(flag && curr_state == AT_END_BOOL_TRUE)
		 {
		 	if(json[i] == ' '||json[i] == '\n'||json[i] == '\t')
		 	{
		 		curr_state = AT_END_BOOL_TRUE;
		 	}

		 	else if(json[i] == ',')
		    {
		       	curr_state = AT_COMMA_ARRAY;
		    }

		      else if(json[i] == ']')
		       {
		       		curr_state = FINAL_STATE_ARRAY;
		       		flag = true;
		       		break;
		       }

		       else
		       {
		       		curr_state = DEAD_STATE_ARRAY;
		       		flag = false;
		       		
		       }

		 }

		  else if(flag && curr_state == AT_END_BOOL_FALSE)
		 {
			 	if(json[i] == ' '||json[i] == '\n'||json[i] == '\t')
			 	{
			 		curr_state = AT_END_BOOL_FALSE;
			 	}

			 	else if(json[i] == ',')
			    {
			       	curr_state = AT_COMMA_ARRAY;
			    }

		        else if(json[i] == ']')
		       {
		       		curr_state = FINAL_STATE_ARRAY;
		       		flag = true;
		       		break;
		       }

		        else
		       {
		       		curr_state = DEAD_STATE_ARRAY;
		       		flag = false;
		       		
		       }

		 }
		 
		    else if(flag && curr_state == AT_JSON_OBJECT_END )
		    {
				if(json[i] == ' '||json[i] == '\n'||json[i] == '\t')
	    	   {
				  curr_state = AT_JSON_OBJECT_END;
		       }		    	

		       else if(json[i] == ',')
		       {
		       		curr_state = AT_COMMA_ARRAY;
		       }

		       else if(json[i] == ']')
		       {
		       		curr_state = FINAL_STATE_ARRAY;
		       		flag = true;
		       		break;
		       }

		       else
		       {
		       		curr_state = DEAD_STATE_ARRAY;
		       		flag = false;
		       		
		       }
		
		    }

		    else if(flag && curr_state == AT_END_NULL_VALUE)
		    {
		    	if(json[i] == ' '|| json[i] == '\n' || json[i] == '\t')
		    	{
		    		curr_state = AT_END_NULL_VALUE;
		    	}

		    	else if(json[i] == ',')
		    	{
		    		curr_state = AT_COMMA_ARRAY;
		    	}

		    	else if(json[i] == ']')
		    	{
		    		curr_state = FINAL_STATE_ARRAY;
		    		flag = true;
		    		break;
		    	}
		    }

		    else if(flag && curr_state == AT_COMMA_ARRAY)
		    {
		    	if(json[i] == ' '|| json[i] == '\n' || json[i] == '\t')
		    	{
		    		curr_state = AT_COMMA_ARRAY;
		    	}

		    	 else if(json[i]=='{')
			    {
			    	pp res = json_object(json,i+1);
			    	flag = res.first;
			    	i = res.second;
			    	if(flag) curr_state = AT_JSON_OBJECT_END;
			    }

			    else if(json[i] == '[')
			    {
			    	curr_state = AT_START_JSON_ARRAY;
			    	pp res = json_array(json,i+1);
			    	flag = res.first;
			    	i = res.second;
			    	if(flag) curr_state = AT_JSON_ARRAY_END;
			    }

			    else if(json[i] == '\"')
			    {
			    	curr_state = AT_ARRAY_START_STRING;
			    }

			    else if(json.substr(i,4) == "true")
			    {
			    	curr_state = AT_END_BOOL_TRUE;
			    	i += 3;
			    }

			    else if(json.substr(i,5) == "false")
			    {
			    	curr_state = AT_END_BOOL_FALSE;
			    	i += 4;
			    }

		    	else if(json[i]>='0'&&json[i]<='9')
		    	{
		    		curr_state = AT_START_INT;
		    	}

		    	else if(json.substr(i,4)=="null")
		    	{
		    		curr_state = AT_END_NULL_VALUE;
		    	}

		    	else
		    	{
		    		flag = false;
		    		curr_state = DEAD_STATE_ARRAY;
		    	}

			  }

			    else if(flag && curr_state == FINAL_STATE_ARRAY)
			    {
			    	flag = true;
			    	break;	
			    }

	}

	cout<<"@ "<<arraystr[curr_state]<<" "<<json[i]<<" "<<i<<" "<<flag<<"\n";

	if(curr_state == FINAL_STATE_ARRAY && flag) return {true,i};

	return {false,i};	

}


pp  json_parser::json_object(string json,int curr)
{	
	JSON_OBJECT_STATE curr_state = START_OF_JSON;

	cout<<"\n & "<<objstr[curr_state]<<" "<<json[curr]<<"\n";

	unordered_set<string> dup;

	string temp;

	int flag = true,i = curr;

	for(;i<json.size()&&flag;i++)
	{
		cout<<"! "<<objstr[curr_state]<<" "<<json[i]<<" "<<i<<" "<<"\n";

		if(curr_state==INITIAL_STATE)
		{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
     			{
		     		curr_state = INITIAL_STATE;
	    		}

	    		else if(json[i]=='{')
	    		{

	    			pp  res = json_object(json,i+1);	    			
	    			flag = res.first;
	    			i = res.second+1;
	    			if(flag) curr_state = FINAL_STATE;
	    		}

	    		else
	    		{
	    			cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<curr_state<<"\n";
	    			flag = false;
	    			curr_state = DEAD_STATE;
	    		}
	
			}
			
			else if(flag&&curr_state==START_OF_JSON)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
     			{
		     		curr_state = START_OF_JSON;
	    		}

	    		else if(json[i]=='\"')
	    		{

	    			curr_state = AT_START_OF_KEY_STRING;
	    			cout<<" triggered at_start_key_string "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";

	    		}

	    		else if(json[i]=='}')
	    		{
	    			curr_state = FINAL_STATE;
	    			flag = true;
	    			break;
	    		}

	    		else 
	    		{
	    			//cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<curr_state<<"\n";
	    			flag = false;
	    			curr_state =DEAD_STATE;
	    			cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";
	    		}
			}

			else if(flag&&curr_state==AT_START_OF_KEY_STRING)
			{
				
				if(json[i] == '\\')
				{
					curr_state = AT_START_OF_KEY_STRING;
					i += 1;
				}

				else if(json[i]=='\"')
				{	

					if(dup.find(temp)!=dup.end())
					{
						flag = false;
						curr_state = DEAD_STATE;
						cout<<" contain dup key \n";
					}

					else
					{
						dup.insert(temp);
					}

					cout<<"key --> "<<temp<<"\n";
					temp.clear();
					curr_state = END_OF_KEY_STRING;
				} 

				else
				{
					temp.push_back(json[i]);
					curr_state = AT_START_OF_KEY_STRING;
				}

			}

			else if(flag&&curr_state==END_OF_KEY_STRING)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = END_OF_KEY_STRING;
				}

				else if(json[i]==':')
				{
					curr_state = AT_KEY_VALUE_SEPERATOR;
			    }

			    else
			    {
			    	flag = 0;
			    	curr_state = DEAD_STATE;
			    }
			}

			else if(flag&&curr_state==AT_KEY_VALUE_SEPERATOR)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = AT_KEY_VALUE_SEPERATOR;
				}

				else if(json[i]=='f')
				{
					curr_state = AT_START_OF_BOOL_FALSE;
				}

				else if(json[i]=='n')
				{
					curr_state = AT_START_OF_NULL_VALUE;
				}

				else if(json[i]=='t')
				{
					curr_state = AT_START_OF_BOOL_TRUE;
				}

				else if(json[i] >= '0' && json[i] <= '9' || json[i] == '-')
				{
					curr_state = AT_START_OF_VALUE_NUM;
					cout<<"triggered : "<<objstr[curr_state]<<" "<<json[i]<<"\n";
				}

				else if(json[i]=='\"')
				{
					curr_state = AT_START_OF_STRING_VALUE;
				}

				else if(json[i]=='[')
				{
					pp res = json_array(json,i+1);
					flag = res.first;
					i = res.second;
					if(flag) curr_state = JSON_ARRAY_END;
				}

				else if(json[i]=='{')
				{
					pp res = json_object(json,i+1);
					flag = res.first;
					i = res.second;
					cout<<"\n res "<<res.first<<" "<<json[res.second]<<" "<<json[res.second+1]<<(i==json.size()-1)<<" "<<i<<" "<<"\n";
					if(flag) curr_state = JSON_OBJECT_END;
				}

				else
				{
					flag = false;
					curr_state = DEAD_STATE;
				}
			}

			else if(flag && curr_state == JSON_OBJECT_END)
			{
				if(json[i] == ' '||json[i] == '\n'||json[i] == '\t')
				{
					curr_state = JSON_OBJECT_END;
				}

				else if(json[i] == ',')
				{
					curr_state = AT_COMMA;
				}

				else if(json[i] == '}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}

				else
				{
					curr_state = DEAD_STATE;
					flag = false;
				}	
			}

			else if(flag&&curr_state==JSON_ARRAY_END)
			{
				if(json[i] == ' '||json[i] == '\n'||json[i] == '\t')
				{
					curr_state = JSON_ARRAY_END;
				}

				else if(json[i] == ',')
				{
					curr_state = AT_COMMA;
				}

				else if(json[i] == '}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}

				else
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag&&curr_state==AT_START_OF_STRING_VALUE)
			{	

				if(json[i] == '\\')
				{
					curr_state = AT_START_OF_STRING_VALUE;
					i += 1;
				}

				else if(json[i]=='\"')
				{
					curr_state = END_OF_STRING_VALUE;
				}

				else curr_state = AT_START_OF_STRING_VALUE;
			}

			else if(flag&&curr_state==END_OF_STRING_VALUE)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = END_OF_STRING_VALUE;
				}

				else if(json[i]=='}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}

				else if(json[i]==',')
				{
					curr_state = AT_COMMA;	
				}

				else
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag&&curr_state==AT_START_OF_VALUE_NUM)
			{
				if(isdigit(json[i]))
				{
					curr_state = AT_START_OF_VALUE_NUM;
				}

				else if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = END_OF_VALUE_NUM;
				}

				else if(json[i] == ',')
				{
					curr_state = AT_COMMA;
				}

				else 
				{
					curr_state = DEAD_STATE;
					flag = false;
				}

			}

			else if(flag && curr_state == END_OF_VALUE_NUM)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = END_OF_VALUE_NUM;
				}

				else if(json[i]==',')
				{
					curr_state = AT_COMMA;
				}

				else if(json[i] == '}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}

				else
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag && curr_state == AT_START_OF_BOOL_TRUE)
			{
				cout<<"\n wow "<<json.substr(i,3)<<"\n";
				if(json.substr(i,3)=="rue")
				{
					curr_state = AT_END_OF_BOOL_TRUE;
					i += 2;
				}

				else
				{
					curr_state = DEAD_STATE;
     				flag = false;
				}
			}

			else if(flag&&curr_state==AT_END_OF_BOOL_TRUE)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = AT_END_OF_BOOL_TRUE;
				}

				else if(json[i]==',')
				{
					curr_state = AT_COMMA;
				}

				else  if(json[i]=='}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}	

				else 
				{
					flag = false;
					curr_state = DEAD_STATE;
				}
			}

			else if(flag&&curr_state==AT_START_OF_BOOL_FALSE)
			{
				cout<<"\n wow "<<json.substr(i,5)<<"\n";
				if(json.substr(i,4)=="alse")
				{
					curr_state = AT_END_OF_BOOL_FLASE;

					i += 3;
				}

				else 
				{
					curr_state = DEAD_STATE;

					flag = false; 
				}
			}

			else if(flag&&curr_state==AT_END_OF_BOOL_FLASE)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = AT_END_OF_BOOL_FLASE;
				}

				else if(json[i]==',')
				{
					curr_state = AT_COMMA;
				}

				else if(json[i]=='}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				}

				else
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag&&curr_state==AT_START_OF_NULL_VALUE)
			{

				cout<<" wow "<<json.substr(i,3)<<"\n";

				if(json.substr(i,3)=="ull")
				{
					curr_state = AT_END_OF_NULL_VALUE;
					i += 2;
				}

				else 
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag&&curr_state==AT_END_OF_NULL_VALUE)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = AT_END_OF_NULL_VALUE;
				}

				else if(json[i]==',')
				{
					curr_state = START_OF_JSON;
				}

				else if(json[i]=='}')
				{
					curr_state = FINAL_STATE;
					flag = true;
					break;
				} 

				else 
				{
					curr_state = DEAD_STATE;
					flag = false;
				}
			}

			else if(flag && curr_state == AT_COMMA)
			{
				if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
     			{
		     		curr_state = AT_COMMA;
	    		}

	    		else if(json[i]=='\"')
	    		{

	    			curr_state = AT_START_OF_KEY_STRING;
	    			cout<<" triggered at_start_key_string "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";

	    		}

	    		else 
	    		{
	    			//cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<curr_state<<"\n";
	    			flag = false;
	    			curr_state =DEAD_STATE;
	    			cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";
	    		}
			}	

			//indx = i;

		}

	



	cout<<"@ "<<objstr[curr_state]<<" "<<flag<<" "<<i<<" "<<json[i]<<" \n";

	if((curr_state == FINAL_STATE && flag == true)) return {true,i}; 

	return {false,i};

}



int json_parser::parser(string json)
{
	int index = 0,count = 0;

	bool flag = true;

	for(;index < json.size() && flag && count <2;index++)
	{

		if(json[index]=='[' )
		{
			pp res =  json_array(json,index+1);
			flag = res.first;
			index =  res.second+1;
			cout<<"% "<<index<<" "<<json[index]<<"\n";
			count++;
		}

		else if(json[index]=='{')
		{
			pp res =  json_object(json,index+1);
			flag = res.first;
			index = res.second+1;
			cout<<"~ "<<index<<" "<<json[index]<<"\n";
			count++;
		}

		else if(json[index]==' '||json[index]=='\n'||json[index]=='\t')
		{
			continue;
		}

		else 
		{
			flag = false;
		}

	}

//	cout<<"\n* "<<json[95]<<" "<<flag<<"\n";
// cout<<"\n\n****\n";
// 	// 
// 	for(int j = 33827;j<=33847;j++)
// 	{
// 		cout<<json[j]<<" ";
// 	}

	cout<<"\n";

	return (flag == true && count == 1); 
}



int main()
{	

	string file; cin>>file;

	ifstream myfile(file.c_str());

	string json, line;

	if(!myfile) 
	{
		cout<<"No such File\n"; return 0;
	}	

	while(getline(myfile,line))
	{
		json += line;

		cout<<line<<"\n";
	}
	
	cout<<"\n\n"<<json<<"\n";

	myfile.close();

	json_parser jp;

	cout<<"\nIs valid : "<<jp.parser(json)<<"\n";
    


}