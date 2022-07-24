package parser.states.json;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;
import parser.utils.ParserUtils;

public class JsonKeyValueSep extends State {
	private String subState;
	
	public JsonKeyValueSep() {
		this.subState = JsonConstants.JSON_START_OF_KEY_VALUE_SEP;
	}
	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {

		System.out.println("Inside Json Key Value Sep "+ index);
		Integer jsonSize = json.length()-1;
		String currentChar = null;
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
			
			System.out.println(currentChar + " "+index.getInt());
			
			if(!JsonConstants.E_NEW_LINE.contains(currentChar)) {
				
				if(JsonConstants.COLON.equals(currentChar)) {
					
					if(JsonConstants.JSON_START_OF_KEY_VALUE_SEP.equals(getSubState())) {
						setSubState(JsonConstants.JSON_AT_KEY_VALUE_SEP);
					}
					
					else {// Failed State
						System.out.println("failed");
						return StaticMethods.getState(-1);
					}
				}
				else {
					switch(currentChar) {
						
						case JsonConstants.QUOTES:
							//Json String Value
							return StaticMethods.getState(4);
						
						case JsonConstants.CHAR_T:
							TransitionRules.setBoolRule(true);
							return StaticMethods.getState(5);
						
						case JsonConstants.CHAR_F:
							TransitionRules.setBoolRule(false);
							return StaticMethods.getState(5);
						
						case JsonConstants.NULL:
							StaticMethods.getState(6);
							return null;
						
						case JsonConstants.JSON_START:
							TransitionRules.setIsSubJson(true);
							return StaticMethods.getState(1);
						
						case JsonConstants.JSON_ARRAY_START:
							TransitionRules.setIsSubJson(true);
							return StaticMethods.getState(9);
						
						default:
							if(ParserUtils.isInt(currentChar,true)) {
								System.out.println("Checking Int");
								return StaticMethods.getState(7); //Int state
							}
							else {
								System.out.println("//Failed");
								return StaticMethods.getState(-1);  //failed
							} 
					}
				}
				
			}
						
			
			index.Increment();
		}
		
		return null;
	}
	
	public String getSubState() {
		return this.subState;
	}
	
	public void setSubState(String stateName) {
		this.subState = stateName;
	}
	
	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
