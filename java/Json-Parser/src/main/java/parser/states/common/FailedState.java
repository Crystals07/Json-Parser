package parser.states.common;

import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

public class FailedState extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		return StaticMethods.getState(-1);
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
