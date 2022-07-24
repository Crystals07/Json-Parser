package parser.states.common;

import parser.constants.ConstantsNumbers;
import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;

public class BoolState extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		Integer jsonSize = json.length()-1;
		Integer i = index.getInt();
		
		if(TransitionRules.getBoolRule()) {
			if(jsonSize.compareTo(i+2)>=0) {
				index.setNum(i+2);
				return StaticMethods.getState(JsonConstants.TRUE.equals(json.substring(i-1,i+3))?8:-1);
			}
			else {
				return null; //Failed State
			}
		} 
		else {
			if(jsonSize.compareTo(i+3)>=0) {
				index.setNum(i+3);
				return StaticMethods.getState(JsonConstants.FALSE.equals(json.substring(i-1,i+4))?8:-1);
			}
			else {
				return null; //Failed State
			}
		}
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
