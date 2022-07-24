package parser.states.json;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

public class JsonStringValue extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {

		Integer jsonSize = json.length()-1;
		String currentChar = null;
		System.out.println(index);
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
						
			if(JsonConstants.QUOTES.equals(currentChar)) {
				if(!JsonConstants.ESC_CHR.equals(StaticMethods.getPrevChar(json,index))) {
					//Value Value Key Sep
					return StaticMethods.getState(8);
				}
			}
			
			else if(JsonConstants.NEW_LINE.contains(currentChar)){
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
