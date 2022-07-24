package parser.states.array;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;

public class ArrayKeyValueSep extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		Integer jsonSize = json.length()-1;
		String currentChar = null;
		
		
		while(index.getInt()<jsonSize) {
			
			 currentChar = Character.toString(json.charAt(index.getInt())); 
			if(!JsonConstants.E_NEW_LINE.contains(currentChar)) {
				
				if(JsonConstants.COMA.equals(currentChar)) {
					TransitionRules.setArrayRule(true);
					return null; // Start of ARRAY
				}
				
				else if(JsonConstants.JSON_ARRAY_END.equals(currentChar)) {
					
					if(!TransitionRules.checkArrayRule()) {
						return null; // End of Json Array
					}
					
					else {
						return StaticMethods.getState(-1); //Failed State
					}
				}
				
			}
			
		}
		return null;
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
