package parser.states.array;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

public class ArrayStringValue extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		Integer jsonSize = json.length()-1;
		String currentChar;
		
		while(index.getInt()<=jsonSize) {
			currentChar = Character.toString(json.charAt(index.getInt()));
			if(!JsonConstants.SPACE_TAB.contains(currentChar)) {
				
				if(JsonConstants.QUOTES.equals(currentChar)) {
					if(!JsonConstants.ESC_CHR.equals(StaticMethods.getPrevChar(json, index))) {
						return null; //Array Key Value Sep
					}
				}
				
				else {
					return StaticMethods.getState(-1); //Failed State
				}
			}
		}
		
		return StaticMethods.getState(-1); //Failed State
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
