package parser.states.json;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;

public class JsonEnd extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		System.out.println("Inside Json End");
		Integer jsonSize = json.length()-1;
		String currentChar;
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
			
			if(!JsonConstants.E_NEW_LINE.contains(currentChar)) {
				if(JsonConstants.COMA.equals(currentChar)) {
					if(TransitionRules.getIsSubJson()) {
						TransitionRules.setIsSubJson(false);
						return StaticMethods.getState(1);     //Start of Json
					}
					
					else {
						return StaticMethods.getState(-1); //Failed State
					}
				}
				
				else {
					return StaticMethods.getState(-1); //Failed State
				}
			}
			
			index.Increment();
		}
		
		return StaticMethods.getState(13); //Json End State
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
