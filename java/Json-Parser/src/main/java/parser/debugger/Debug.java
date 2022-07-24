package parser.debugger;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import parser.constants.JsonConstants;
import parser.states.State;

public class Debug {
	private int dept;
	private State currentstate;
	private List<State> statestack;
	private Map<State,String> stateres = new HashMap<State,String>();
	private String errorMessage;
	
	public String getEerrorMessage() {
		return errorMessage;
	}
	
	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}

	public String getErrorSegment(String json, Integer index) {
		// TODO Auto-generated method stub
		return json.substring(0, ((index)>JsonConstants.ERROR_SEGMENT_DEFAULT ?JsonConstants.ERROR_SEGMENT_DEFAULT:index));
	}

	public int getDept() {
		// TODO Auto-generated method stub
		return this.dept;
	}
	
	public void printstack() {
		//StringBuilder sb = new StringBuilder();
		//Comming soon
	}
}
