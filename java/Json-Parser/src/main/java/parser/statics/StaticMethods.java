package parser.statics;

import parser.states.*;
import parser.states.array.ArrayEnd;
import parser.states.array.ArrayKeyValueSep;
import parser.states.array.ArrayStart;
import parser.states.array.ArrayStringValue;
import parser.states.common.BoolState;
import parser.states.common.FailedState;
import parser.states.common.IntState;
import parser.states.common.NullState;
import parser.states.common.StartState;
import parser.states.json.JsonEnd;
import parser.states.json.JsonKey;
import parser.states.json.JsonKeyValueSep;
import parser.states.json.JsonStart;
import parser.states.json.JsonStringValue;
import parser.states.json.JsonValueKeySep;
import parser.utils.MutableInt;

public class StaticMethods {
	
	private static final State states[] = {new StartState(),new JsonStart(),new JsonKey(),new JsonKeyValueSep(),new JsonStringValue(),new BoolState(),new NullState(),
										   new IntState(),new JsonValueKeySep(),new ArrayStart(),new ArrayStringValue(),new ArrayKeyValueSep(),new ArrayEnd(),
										   new JsonEnd(),new FailedState()}; 
	
	public static State getState(Integer stateNumb) {
		return states[(stateNumb<0 ? 14:stateNumb)];
	}

	public static String getPrevChar(String json, MutableInt index) {
		// TODO Auto-generated method stub
		return Character.toString(json.charAt(index.getInt()-1));
	}
	
}
