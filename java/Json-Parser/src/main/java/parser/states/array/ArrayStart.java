package parser.states.array;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;
import parser.utils.ParserUtils;

public class ArrayStart extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
				System.out.println("Inside Array Start ");
				Integer jsonSize = json.length()-1;
				String currentChar = null;
				//System.out.println(index);
				
				while(index.getInt()<=jsonSize) {
					
					 currentChar = Character.toString(json.charAt(index.getInt()));
					
					 if(!JsonConstants.E_NEW_LINE.contains(currentChar)){
						
						 switch(currentChar) {
						 case JsonConstants.QUOTES:
							 	TransitionRules.setArrayRule(false);
								return null;
							
							case JsonConstants.CHAR_T:
								TransitionRules.setArrayRule(false);
								TransitionRules.setBoolRule(true);
								return null;
							
							case JsonConstants.CHAR_F:
								TransitionRules.setArrayRule(false);
								TransitionRules.setBoolRule(false);
								return null;
							
							case JsonConstants.NULL:
								TransitionRules.setArrayRule(false);
								return null;
							
							case JsonConstants.JSON_START:
								TransitionRules.setArrayRule(false);
								TransitionRules.setIsSubJson(true);
								return null;
							
							case JsonConstants.JSON_ARRAY_START:
								TransitionRules.setArrayRule(false);
								TransitionRules.setIsSubArray(true);
								return null;
							
							default:
								if(ParserUtils.isInt(currentChar,true)) {
									TransitionRules.setArrayRule(false);
									return null; //Int state
								}
								else return StaticMethods.getState(-1);  //failed
						 }
						
					}
					
					index.Increment();
				}
				
				return StaticMethods.getState(-1); //Failed state
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
