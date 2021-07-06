#include<bits/stdc++.h>
using namespace std;

#define pp pair<int,int>

char deb = 'd';

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

	bool is_dec = false;


	int i=curr;

	for(;i<json.size() && flag;i++)
	{	
		if(deb=='d')cout<<"--> "<<arraystr[curr_state]<<" "<<json[i]<<" "<<i<<endl;

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

	    	else if(json[i]>='0'&&json[i]<='9'||json[i] == '-')
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
		 	if(json[i]>='0'&&json[i]<='9')
		 	{
		 		curr_state = AT_START_INT;
		 	}

		 	else if(json[i] == ' '||json[i] == '\n' || json[i] == '\t' )
		 	{
		 		curr_state = AT_END_INT;
		 		is_dec = false;
		 	}

		 	else if(json[i] == ',')
		 	{
		 		curr_state = AT_COMMA_ARRAY;
		 		is_dec = false;
		 	}

		 	else if(json[i] == '.' && (json[i-1]>='0'&&json[i-1]<='9') && (json[i+1] >='0' && json[i+1] <='9'))
		 	{
		 		if(is_dec == false) is_dec = true;

		 		else
		 		{
		 			flag = false;
		 			curr_state = DEAD_STATE_ARRAY;
		 		}
		 	}

		 	else 
		 	{
		 		flag = false;
		 		curr_state = DEAD_STATE_ARRAY;

		 	}
		 }

		 else if(flag && curr_state == AT_END_INT)
		 {
		 	if(json[i] == ' '|| json[i] == '\n' || json[i] == '\t')
		 	{
		 		curr_state = AT_END_INT;
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

		    	else
		    	{
		    		curr_state = DEAD_STATE_ARRAY;
		    		flag = false;
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

		    	else if(json[i]>='0'&&json[i]<='9'||json[i] == '-')
		    	{
		    		curr_state = AT_START_INT;
		    	}

		    	else if(json.substr(i,4)=="null")
		    	{
		    		curr_state = AT_END_NULL_VALUE;
		    		i += 3;
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

	if(deb=='d')cout<<"@ "<<arraystr[curr_state]<<" "<<json[i]<<" "<<i<<" "<<flag<<"\n";

	if(curr_state == FINAL_STATE_ARRAY && flag) return {true,i};

	return {false,i};	

}


pp  json_parser::json_object(string json,int curr)
{	
	JSON_OBJECT_STATE curr_state = START_OF_JSON;

	if(deb=='d')cout<<"\n & "<<objstr[curr_state]<<" "<<json[curr]<<"\n";

	bool is_dec = false;

	unordered_set<string> dup;

	string temp;

	int flag = true,i = curr;

	for(;i<json.size()&&flag;i++)
	{
		if(deb=='d')cout<<"! "<<objstr[curr_state]<<" "<<json[i]<<" "<<i<<" "<<"\n";

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

	    		if(deb=='d') cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<curr_state<<"\n";
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
	    		if(deb=='d')	cout<<" triggered at_start_key_string "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";

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
	    			if(deb=='d') cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";
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
						if(deb=='d') cout<<" contain dup key \n";
					}

					else
					{
						dup.insert(temp);
					}
					if(deb=='d') cout<<"key --> "<<temp<<"\n";
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
					if(deb=='d') cout<<"triggered : "<<objstr[curr_state]<<" "<<json[i]<<"\n";
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
				if(deb=='d') cout<<"\n res "<<res.first<<" "<<json[res.second]<<" "<<json[res.second+1]<<(i==json.size()-1)<<" "<<i<<" "<<"\n";
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
				if(json[i]>='0'&&json[i]<='9')
				{
					curr_state = AT_START_OF_VALUE_NUM;
				}

				else if(json[i]==' '||json[i]=='\n'||json[i]=='\t')
				{
					curr_state = END_OF_VALUE_NUM;
					is_dec = false;
				}

				else if(json[i] == '.' && (json[i-1] >='0' && json[i-1] <='9') &&  (json[i+1] >='0' && json[i+1] <='9'))
				{
					if(deb=='d') cout<<" dec "<<is_dec<<"\n";

					if(is_dec == false) is_dec = true;

					else
					{
						flag = false;
						curr_state = DEAD_STATE;
					}
				}

				else if(json[i] == ',')
				{
					curr_state = AT_COMMA;
					is_dec = false;
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
					is_dec = false;
				}

				else if(json[i]==',')
				{
					curr_state = AT_COMMA;
					is_dec = false;
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
				if(deb=='d') cout<<"\n wow "<<json.substr(i,3)<<"\n";
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
				if(deb=='d') cout<<"\n wow "<<json.substr(i,5)<<"\n";
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

				if(deb=='d')cout<<" wow "<<json.substr(i,3)<<"\n";

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
	    			if(deb=='d')cout<<" triggered at_start_key_string "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";

	    		}

	    		else 
	    		{
	    			//cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<curr_state<<"\n";
	    			flag = false;
	    			curr_state =DEAD_STATE;
	    			if(deb=='d')cout<<" triggered else dead initial "<<i<<" "<<json[i]<<" "<<objstr[curr_state]<<"\n";
	    		}
			}	

			//indx = i;

		}

	



	if(deb=='d') cout<<"@ "<<objstr[curr_state]<<" "<<flag<<" "<<i<<" "<<json[i]<<" \n";

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
		  if(deb=='d')	cout<<"% "<<index<<" "<<json[index]<<"\n";
			count++;
		}

		else if(json[index]=='{')
		{
			pp res =  json_object(json,index+1);
			flag = res.first;
			index = res.second+1;
		  if(deb=='d')cout<<"~ "<<index<<" "<<json[index]<<"\n";
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

	cout<<"\n";

	return (flag == true && count == 1); 
}



int main(int arno,char** args)
{	

	deb = *(args[1]);

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

	if(deb=='d')	cout<<line<<"\n";
	}
	
	if(deb=='d') cout<<"\n\n"<<json<<"\n";

	myfile.close();

	json_parser jp;

	cout<<(jp.parser(json)?"Valid Json ":"Invalid Json")<<"\n";
    


}