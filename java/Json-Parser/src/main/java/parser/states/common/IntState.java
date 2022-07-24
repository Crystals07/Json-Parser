package parser.states.common;

import parser.constants.ConstantsNumbers;
import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.State;
import parser.statics.StaticMethods;
import parser.statics.TransitionRules;
import parser.utils.MutableInt;
import parser.utils.ParserUtils;

public class IntState extends State {

	@Override
	public State parse(String json, MutableInt index, boolean debugflag, Debug dobj) {
		// TODO Auto-generated method stub
		Integer jsonSize = json.length()-1;
		Boolean decimalFlag = false;
		Boolean startNumSign = false;
		String currentChar;
		StringBuilder num = new StringBuilder();
		
		while(index.getInt()<=jsonSize) {
			
			currentChar = Character.toString(json.charAt(index.getInt()));
			
			System.out.println(" char "+ currentChar);
			
			if(!ParserUtils.isInt(currentChar, false)) {
				if(JsonConstants.DOT_CHAR.equals(currentChar) && !decimalFlag) {
					decimalFlag = true;
				}
				
				else if(JsonConstants.E_NEW_LINE.contains(currentChar)||JsonConstants.COMA.equals(currentChar)) {
					TransitionRules.setJsonRule(true);
					return StaticMethods.getState(8); // Json Value Key Sep
				}
				
				else {
					return StaticMethods.getState(-1); // Failed State
				}
			}
			
			index.Increment();
			
		}
		
		return StaticMethods.getState(-1);
	}

	@Override
	public String getStateName() {
		// TODO Auto-generated method stub
		return null;
	}

}
