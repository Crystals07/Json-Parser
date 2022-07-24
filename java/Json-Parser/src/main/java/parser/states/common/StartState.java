package parser.states.common;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

public class StartState extends State{
	
	

	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {

		System.out.println("Inside Start State");
		Integer jsonSize = json.length()-1;
		String currentChar = null;
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
			
			if(JsonConstants.JSON_START.equals(currentChar)) {
				//Json Start State
				return StaticMethods.getState(1);
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
