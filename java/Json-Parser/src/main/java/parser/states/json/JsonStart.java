package parser.states.json;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;

public class JsonStart extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {

		System.out.println("Inside Json Start State "+index);
		Integer jsonSize = json.length()-1;
		String currentChar = null;
		System.out.println(index);
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
						
			if(JsonConstants.QUOTES.equals(currentChar)) {
				TransitionRules.setJsonRule(false);
				return StaticMethods.getState(2);
			}
			
			else if(!JsonConstants.E_NEW_LINE.contains(currentChar)){

				if(JsonConstants.JSON_END.equals(currentChar) && !TransitionRules.checkJsonRule()) {
					//JSON END
					return StaticMethods.getState(13);
				}
				else {
					//Failed State
					return StaticMethods.getState(-1);
				}
				
			}
			
			index.Increment();
		}
		
		//Failed State
		return StaticMethods.getState(-1);
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
