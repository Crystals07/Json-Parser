package parser.states;

import java.util.HashSet;
import java.util.Set;

import parser.debugger.Debug;
import parser.utils.MutableInt;

public abstract class State {
	private String stateName;
	public static Set<String> uniqueKey = new HashSet<>();
	public abstract State parse(String json,MutableInt index,boolean debugflag,Debug dobj);
	public abstract String getStateName();
	
}
