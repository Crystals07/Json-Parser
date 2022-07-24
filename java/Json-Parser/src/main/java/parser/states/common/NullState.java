package parser.states.common;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

public class NullState extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		Integer i = index.getInt();
		Integer jsonSize = json.length()-1;
		
		if(jsonSize.compareTo(i+2)>=0) {
			index.setNum(i+2);
			return StaticMethods.getState(JsonConstants.NULL.equals(json.substring(i-1,i+3))?8:-1);
		}
		//failed state
		return null;
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
