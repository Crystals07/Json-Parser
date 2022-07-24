package parser.driver;

import parser.constants.JsonConstants;
import parser.debugger.Debug;
import parser.states.*;
import parser.states.array.ArrayEnd;
import parser.states.array.ArrayStart;
import parser.states.common.FailedState;
import parser.states.json.JsonEnd;
import parser.states.json.JsonStart;
import parser.statics.StaticMethods;
import parser.utils.MutableInt;

import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

//import javafx.util.Pair;

public class JsonParser {
	
	public boolean parse(String json) {
		return parse(json,false);
	}
	
	public boolean parse(String json,boolean debug) {
    if(json==null||json.isEmpty()) return false;
		
		Debug dobj = new Debug();
		MutableInt index = new MutableInt();
		Integer jsonSize = json.length()-1;
		Integer count = 0;
		State currentState = StaticMethods.getState(0);
		String currentChar = null;
		
		for(int i=0;i<=jsonSize;i++) {
			System.out.println( i+ " ## "+ json.charAt(i));
		}
		
		while((index.getInt() <=jsonSize)) {
			
			currentState = currentState.parse(json, index,false,null);
			
			if(currentState instanceof FailedState||count>1) {
				return false;
			}
			
			if(currentState instanceof JsonStart) {
				
				index.Increment();
				currentState = parse_object(json,index);
				count++;
			}
			
			else if(currentState instanceof ArrayStart) {
				
				index.Increment();
				currentState = parse_array(json,index);
				count++;
			}
			
			else if(currentState instanceof JsonEnd || currentState instanceof ArrayEnd) {
				//break;
			}
			
			
			index.Increment();
		}
			
		return ((currentState instanceof JsonEnd || currentState instanceof ArrayEnd) && count.equals(new Integer(1)));
	}
	
	private State parse_object(String json,MutableInt index) {

		Integer jsonSize = json.length()-1;
		State currentState = StaticMethods.getState(1);
		
		while((index.getInt() <=jsonSize)) {
			
			currentState = currentState.parse(json, index,false,null);
			
			if(currentState instanceof FailedState) {
				//Failed State
				return StaticMethods.getState(-1);
			}
			
			if(currentState instanceof JsonStart) {
				
				currentState = parse_object(json,index);			
			}
			
			
			else if(currentState instanceof ArrayStart) {
				
				currentState = parse_array(json,index);
				
			}
			
			index.Increment();
		}
			
		//Json End
		return currentState;
	}
	private State parse_array(String json,MutableInt index) {
		
		//MutableInt index = new MutableInt();
		Integer jsonSize = json.length()-1;
		State currentState = StaticMethods.getState(9);
		String currentChar = null;
		
		
		while((index.getInt() <=jsonSize)) {
			
			currentState = currentState.parse(json, index,false,null);
			
			if(currentState==null||currentState instanceof FailedState) {
				//Failed State
				return null;
			}
			
			if(currentState instanceof JsonStart) {
				
				currentState = parse_object(json,index);
				
			}
			
			else if(currentState instanceof ArrayStart) {
				
				currentState = parse_array(json,index);
				
			}
			
			index.Increment();
		}
		
		return currentState;
	}
}
