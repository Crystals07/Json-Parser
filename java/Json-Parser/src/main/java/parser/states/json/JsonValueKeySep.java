package parser.states.json;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;

public class JsonValueKeySep extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {

		System.out.println("Inside Json Value Key Sep State ");
		Integer jsonSize = json.length()-1;
		String currentChar = null;
		//System.out.println(index);
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
			
			System.out.println(" # "+index);
			
			if(TransitionRules.checkJsonRule()) {
				TransitionRules.setJsonRule(false);
				return StaticMethods.getState(1); //Json Start
			}
			
			if(JsonConstants.COMA.equals(currentChar)) {
				TransitionRules.setJsonRule(true);
				return StaticMethods.getState(1); //Json Start
			}
			
			else if(!JsonConstants.E_NEW_LINE.contains(currentChar)){
				//Failed State
				return StaticMethods.getState(-1);
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
